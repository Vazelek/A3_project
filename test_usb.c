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

    // delete verrou files if exists
    if(access(".verrouData", F_OK) == 0) { // file exists
        remove(".verrouData");
    }
	if(access(".verrouConsigne", F_OK) == 0) { // file exists
        remove(".verrouConsigne");
    }

    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;

    ftStatus = FT_Open(0, &ftHandle); // Open connection between computer and card
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
    ftStatus = FT_SetTimeouts(ftHandle, 40, 0); // set timeout to 40 ms
    if(ftStatus != FT_OK) {
        printf("FT_SetTimeouts failed\n");
        return 1;
    }

    float cons = consigne(10); // actual instruction
    temp_t temperatures; // indoor and outdoor temperature

    unsigned short int regul = 2; // Regulation method : 1 => TOR, other than 1 => PID
	float tint_old = 15; // previous temperature 
	float tint = 15; // actual temperature
	float cons_old = cons; // previous instruction
	float puissance = 50; // command
	unsigned char premiere_iteration = 1; // 1 if it is the first iteration in while loop
	float pid_i_old = 0; // air under the curve (integral)

    while(cons > 5){ // stop if the instruction is under 5°C
        cons_old = cons; // copy the actual instruction inside the previous one
        cons = consigne(cons); // read consigne.txt file to get the instruction
        tint_old = tint; // copy actual indoor temperature inside the previous one
        ftStatus = read_temp(ftHandle, &temperatures); // read the temperatures sent by the card via USB
        if(ftStatus != FT_OK) {
            printf("read_temp failed\n");
            return 1;
        }
        tint = temperatures.interieure; // copy the indoor temperature inside tint
        puissance = regulation_Global(regul, cons, tint, cons_old, tint_old, &pid_i_old, premiere_iteration); // calculate the command according to the actual and previous temperature and instruction
        visualisationC(puissance); // update "true" or "false" for the heater in data.txt
        visualisationT(temperatures); // update indoor and outdoor temperature in data.txt
        ftStatus = write_puis(ftHandle, puissance); // send puis to the card via USB
        if(ftStatus != FT_OK) {
            printf("write_puis failed\n");
            return 1;
        }
        if(premiere_iteration){
            premiere_iteration = 0;
        }

        Sleep(40); // wait 40 ms before another loop (synchronize with the card)
    }
    FT_Close(ftHandle);
    return 0;

}
