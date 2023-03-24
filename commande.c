#include "commande.h"

FT_STATUS write_puis(FT_HANDLE ftHandle, float puissance){

    DWORD BytesWritten;
    char TxBuffer[1] = {0}; // Contains data to write to device

    TxBuffer[0] = ((unsigned char) ((puissance * 127) / 100)) | ((puissance != 0) << 7);

    return FT_Write(ftHandle, TxBuffer, sizeof(TxBuffer), &BytesWritten);
}


