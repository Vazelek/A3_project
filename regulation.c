#include <stdio.h>
#include <stdlib.h>
#include "regulation.h"

float regulation_TOR(float consigne, float* tabT, int nT){
    if (consigne > tabT[nT-1]){
        return 50;
    }
    else{
        return 0;
    }
}

float regulation_PID(float consigne, float* tabT, int nT){
    float e = consigne - tabT[nT - 1];
    float p_val = e * 1.1;
    float i_val = 0;
    float d_val = 0;

    if(nT > 1){
        for(int i = 0; i < nT; i++){
            i_val += tabT[i];
        }
        i_val *= 0.2;

        d_val = (tabT[nT - 1] - tabT[nT - 2]) * 0.15;
    }

    return p_val + i_val + d_val;
}
	 
float regulationTest(int regul,float consigne,float* tabT, int nT){
    float cmd;

    if(regul == 1){
        cmd = regulation_TOR(consigne, tabT, nT);
    }
    else{
        cmd = regulation_PID(consigne, tabT, nT);
    }
		
	return cmd;
}
    
  
