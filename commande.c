#include "commande.h"

void write_puis(FT_HANDLE ftHandle, float puissance){

    FT_STATUS ftStatus;
    DWORD BytesWritten;
    char TxBuffer = (puissance / 127) * 100; // Contains data to write to device

    ftStatus = FT_Write(ftHandle, &TxBuffer, 1, &BytesWritten);
    if (ftStatus != FT_OK){
        printf("Failed to write send data to the device\n");
    }
}


