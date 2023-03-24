#include <unistd.h>
#include "define.h"
#include "consigne.h"
#include "regulation.h"
#include "simulateur.h"
#include "visualisationC.h"
#include "visualisationT.h"
#include "autotests.h"
#include "releve.h"

int main(){
/*
	if(access(".verrouData", F_OK) == 0) { // file exists
        remove(".verrouData");
    }
	if(access(".verrouConsigne", F_OK) == 0) { // file exists
        remove(".verrouConsigne");
    }

	temp_t temperature;
	temperature.exterieure = 14.0;
	temperature.interieure = 30.0;
	struct simParam_s*  sim_params = simConstruct(temperature);

	int i = 0;
	unsigned short int regul = 2;
	float cmd = 10;
	float puissance = 50;
	float tabT[10000];
	while(cmd <= 5 && i < 10000){
		tabT[i] = temperature.interieure;
		visualisationT(temperature);
		cmd = consigne(cmd);
		puissance = regulationTest(regul, cmd, tabT, i + 1);
		sim_params->tempExt_f = temperature.exterieure;
		sim_params->tempInt_f = temperature.interieure;
		temperature=simCalc(puissance, sim_params);
		visualisationC(puissance);
		i++;
	}

	simDestruct(sim_params); // destruction de simulateur
	return EXIT_SUCCESS;
*/
/*
    float score1=0,score2=0,score3=0,score4=0,score5=0;
    score1 = testVisualisationT();
    score2 = testConsigne();
    score3 = testVisualisationC();
    score4 = testRegulationTOR();
    score5 = testRegulationPID();
    printf("----- Auto tests results: -----\n");
    printf("testVisualisationT\t:    score = %g %%\n",score1*100);
    printf("testConsigne \t\t:    score = %g %%\n",score2*100);
    printf("testVisualisationC\t:    score = %g %%\n",score3*100);
    printf("testRegulationTOR\t:    score = %g %%\n",score4*100);
    printf("testRegulationPID\t:    score = %g %%\n",score5*100);
    return EXIT_SUCCESS;
*/

    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    FT_STATUS ftStatus2;
    FT_STATUS ftStatus3;
    ftStatus = FT_Open(0, &ftHandle);
    if(ftStatus != FT_OK) {
        // FT_Open failed
        return 0;
    }

    ftStatus = FT_SetBaudRate(ftHandle, 115200); // Set baud rate to 115200
    ftStatus2 = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE); // Set 8 data bits, 1 stop bit and no parity
    ftStatus3 = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0x11, 0x13); // No flow and 0x11 and 0x13 are useless
    if (ftStatus == FT_OK && ftStatus2 == FT_OK && ftStatus3 == FT_OK) {
        read_temp(ftHandle);
        return 0; // FT_SetBaudRate OK +  FT_SetDataCharacteristics OK + FT_SetFlowControl OK
    }
    else {
        return 0; // FT_SetBaudRate Failed +-  FT_SetDataCharacteristics Failed +- FT_SetFlowControl Failed
    }
    FT_Close(ftHandle);

}
