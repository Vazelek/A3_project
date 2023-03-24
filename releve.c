#include "releve.h"

FT_STATUS read_temp(FT_HANDLE ftHandle, temp_t *temp){

    FT_STATUS ftStatus;
    DWORD EventDWord;
    DWORD TxBytes;
    DWORD RxBytes;
    DWORD BytesReceived;
    char RxBuffer[6];
    unsigned int tempIntSOT = 0;
    unsigned int tempExtSOT = 0;
    float tempInt = 0;
    float tempExt = 0;

    ftStatus = FT_GetStatus(ftHandle,&RxBytes,&TxBytes,&EventDWord);

    if (RxBytes > 0 && ftStatus == FT_OK) {
        ftStatus = FT_Read(ftHandle,RxBuffer,RxBytes,&BytesReceived);
        if (ftStatus == FT_OK) {

            tempExtSOT |= RxBuffer[0] & 0b1111;
            tempExtSOT |= (RxBuffer[1] & 0b1111) << 4;
            tempExtSOT |= (RxBuffer[2] & 0b1111) << 8;

            tempIntSOT |= RxBuffer[3] & 0b1111;
            tempIntSOT |= (RxBuffer[4] & 0b1111) << 4;
            tempIntSOT |= (RxBuffer[5] & 0b1111) << 8;

            tempExt = -39.64 + 0.04 * tempExtSOT;
            tempInt = -39.64 + 0.04 * tempIntSOT;

            temp->exterieure = tempExt;
            temp->interieure = tempInt;

        }
    }
    return ftStatus;
}


