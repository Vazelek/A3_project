#include <unistd.h>
#include "define.h"
#include "consigne.h"
#include "regulation.h"
#include "visualisationC.h"
#include "visualisationT.h"
#include "releve.h"
#include "commande.h"

int main(){

    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;

    ftStatus = FT_Open(0, &ftHandle);
    if(ftStatus != FT_OK) {
        // FT_Open failed
        return 0;
    }

    ftStatus = FT_SetBaudRate(ftHandle, 115200); // Set baud rate to 115200
    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE); // Set 8 data bits, 1 stop bit and no parity
    ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0x11, 0x13); // No flow and 0x11 and 0x13 are useless
    ftStatus = FT_SetTimeouts(ftHandle, 40, 0);

    while (1){

        read_temp(ftHandle);
    }
    FT_Close(ftHandle);
    return 0;

}
