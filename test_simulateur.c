#include <unistd.h>
#include "define.h"
#include "consigne.h"
#include "regulation.h"
#include "simulateur.h"
#include "visualisationC.h"
#include "visualisationT.h"

int main(){

	printf("Test SIMULATEUR\n\n");

	if(access(".verrouData", F_OK) == 0) { // file exists
        remove(".verrouData");
    }
	if(access(".verrouConsigne", F_OK) == 0) { // file exists
        remove(".verrouConsigne");
    }

	temp_t temperature;
	temperature.exterieure = 14.0; // set tempExt to 14 by default
	temperature.interieure = 15.0; // set tempInt to 15 by default
	struct simParam_s*  sim_params = simConstruct(temperature); // constructor for simulator

	unsigned short int regul = 2; // set the type of simulator (1 = toutou rien, 2 = PID)
	float tint_old = 15; // last tempInt
	float tint = 15; // actual tempInt
	float cons_old = 10; // last instruction
	float cons = 10; // actual instruction
	float puissance = 50;
	unsigned char first = 1; // if it's the first iteration
	float pid_i_old = 0; // last i of PID
	// while the instruction is superior to 5 degree
	while(cons > 5){
		visualisationT(temperature); // actualize in data.txt the temp
		cons_old = cons; // set last instruction
		cons = consigne(cons); // set new instruction
		puissance = regulation_Global(regul, cons, tint, cons_old, tint_old, &pid_i_old, first); // define puissance with the regulation fucntion
		tint_old = tint; // set last tempInt
		temperature = simCalc(puissance, sim_params); // calcul power with the simulator
		tint = temperature.interieure; // set tempInt
		visualisationC(puissance); // actualize in data.txt the heater
		if(first){
			first = 0;
		}
	}

	simDestruct(sim_params); // destruction de simulateur
	return EXIT_SUCCESS;
    
}
