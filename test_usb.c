#include <unistd.h>
#include "define.h"
#include "consigne.h"
#include "regulation.h"
#include "visualisationC.h"
#include "visualisationT.h"
#include "releve.h"
#include "commande.h"

int main(){

	printf("Test USB\n\n");

    if(access(".verrouData", F_OK) == 0) { // file exists
        remove(".verrouData");
    }
	if(access(".verrouConsigne", F_OK) == 0) { // file exists
        remove(".verrouConsigne");
    }

    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;

    ftStatus = FT_Open(0, &ftHandle);
    if(ftStatus != FT_OK) {
        printf("FT_Open failed\n");
        return 1;
    }

    ftStatus = FT_SetBaudRate(ftHandle, 115200); // Set baud rate to 115200
    if(ftStatus != FT_OK) {
        printf("FT_SetBaudRate failed\n");
        return 1;
    }
    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE); // Set 8 data bits, 1 stop bit and no parity
    if(ftStatus != FT_OK) {
        printf("FT_SetDataCharacteristics failed\n");
        return 1;
    }
    ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0x11, 0x13); // No flow and 0x11 and 0x13 are useless
    if(ftStatus != FT_OK) {
        printf("FT_SetFlowControl failed\n");
        return 1;
    }
    ftStatus = FT_SetTimeouts(ftHandle, 40, 0);
    if(ftStatus != FT_OK) {
        printf("FT_SetTimeouts failed\n");
        return 1;
    }

    float cons = consigne(10);
    temp_t temperatures;

    unsigned short int regul = 2;
	float tint_old = 15;
	float tint = 15;
	float cons_old = cons;
	float puissance = 50;
	unsigned char premiere_iteration = 1;
	float pid_i_old = 0;

    while(cons > 5){
        cons_old = cons;
        cons = consigne(cons);
        tint_old = tint;
        ftStatus = read_temp(ftHandle, &temperatures);
        if(ftStatus != FT_OK) {
            printf("read_temp failed\n");
            return 1;
        }
        tint = temperatures.interieure;
        puissance = regulation_Global(regul, cons, tint, cons_old, tint_old, &pid_i_old, premiere_iteration);
        visualisationC(puissance);
        visualisationT(temperatures);
        ftStatus = write_puis(ftHandle, puissance);
        if(ftStatus != FT_OK) {
            printf("write_puis failed\n");
            return 1;
        }
        if(premiere_iteration){
            premiere_iteration = 0;
        }

        Sleep(40);
    }
    FT_Close(ftHandle);
    return 0;

}
