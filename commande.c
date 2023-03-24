#include "commande.h"

FT_STATUS write_puis(FT_HANDLE ftHandle, float puissance){

    DWORD BytesWritten;
    char TxBuffer[1] = {0}; // Contains data to write to device

    // puissance \in [0, 100] and must be send in [0, 127]
    // MSB is 1 if the eater is ON (puissance > 0), 0 otherwise
    TxBuffer[0] = ((unsigned char) ((puissance * 127) / 100)) | ((puissance != 0) << 7);

    return FT_Write(ftHandle, TxBuffer, sizeof(TxBuffer), &BytesWritten); // send data to the card and return status
}


