#include "commande.h"

void write_puis(FT_HANDLE ftHandle, float puissance){

    FT_STATUS ftStatus;
    DWORD BytesWritten;
    char TxBuffer[1] = {0}; // Contains data to write to device

    TxBuffer[0] = ((char) ((puissance / 127) * 100)) | ((puissance != 0) << 7);

    ftStatus = FT_Write(ftHandle, TxBuffer, sizeof(TxBuffer), &BytesWritten);
    if (ftStatus != FT_OK){
        printf("Failed to write send data to the device\n");
    }
}


