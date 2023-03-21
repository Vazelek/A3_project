#include <unistd.h>
#include "define.h"
#include "consigne.h"
#include "regulation.h"
#include "simulateur.h"
#include "visualisationC.h"
#include "visualisationT.h"
#include "autotests.h"

int main(){

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
	while(cmd != 5 && i < 10000){
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
}
