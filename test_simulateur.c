#include <unistd.h>
#include "define.h"
#include "consigne.h"
#include "regulation.h"
#include "simulateur.h"
#include "visualisationC.h"
#include "visualisationT.h"

int main(){

	printf("Test SIMULATEUR\n\n");

	// May be done by make
	if(access(".verrouData", F_OK) == 0) { // file exists
        remove(".verrouData");
    }
	if(access(".verrouConsigne", F_OK) == 0) { // file exists
        remove(".verrouConsigne");
    }

	temp_t temperature;
	temperature.exterieure = 14.0;
	temperature.interieure = 15.0;
	struct simParam_s*  sim_params = simConstruct(temperature);

	unsigned short int regul = 2;
	float tint_old = 15;
	float tint = 15;
	float cons_old = 10;
	float cons = 10;
	float puissance = 50;
	unsigned char first = 1;
	float pid_i_old = 0;
	while(cons > 5){
		visualisationT(temperature);
		cons_old = cons;
		cons = consigne(cons);
		puissance = regulation_Global(regul, cons, tint, cons_old, tint_old, &pid_i_old, first);
		/*sim_params->tempExt_f = temperature.exterieure;
		sim_params->tempInt_f = temperature.interieure;*/
		tint_old = tint;
		temperature = simCalc(puissance, sim_params);
		tint = temperature.interieure;
		visualisationC(puissance);
		if(first){
			first = 0;
		}
	}

	simDestruct(sim_params); // destruction de simulateur
	return EXIT_SUCCESS;
    
}
