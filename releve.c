#include "releve.h"

FT_STATUS read_temp(FT_HANDLE ftHandle, temp_t *temp){

    FT_STATUS ftStatus;
    DWORD EventDWord;
    DWORD TxBytes;
    DWORD RxBytes;
    DWORD BytesReceived;
    char RxBuffer[6]; // we watch 6 bytes to read tempExt and tempInt
    unsigned int tempIntSOT = 0;
    unsigned int tempExtSOT = 0;
    float tempInt = 0;
    float tempExt = 0;

    ftStatus = FT_GetStatus(ftHandle,&RxBytes,&TxBytes,&EventDWord);

    // if we receive bytes and ftStatus = OK
    if (RxBytes > 0 && ftStatus == FT_OK) {
        ftStatus = FT_Read(ftHandle,RxBuffer,RxBytes,&BytesReceived); // read data send by the card
        // read OK
        if (ftStatus == FT_OK) {
            // set tempExtSOT by reading 3 first bytes and taking only first 4 bits
            tempExtSOT |= RxBuffer[0] & 0b1111;
            tempExtSOT |= (RxBuffer[1] & 0b1111) << 4;
            tempExtSOT |= (RxBuffer[2] & 0b1111) << 8;
            // set tempExtSOT by reading 3 last bytes and taking only first 4 bits
            tempIntSOT |= RxBuffer[3] & 0b1111;
            tempIntSOT |= (RxBuffer[4] & 0b1111) << 4;
            tempIntSOT |= (RxBuffer[5] & 0b1111) << 8;
            // convert SOT in real temp
            tempExt = -39.64 + 0.04 * tempExtSOT;
            tempInt = -39.64 + 0.04 * tempIntSOT;
            // return real temp
            temp->exterieure = tempExt;
            temp->interieure = tempInt;

        }
    }
    return ftStatus; 
}


