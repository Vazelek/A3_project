#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
    float dt = 10;
    float e = consigne - tabT[nT - 1];
    if(e <= 0){
        return 0;
    }
    float p_val = e * 1.1;
    float i_val = 0;
    float d_val = 0;

    if(nT > 1){
        for(int i = 0; i < nT - 1; i++){
            i_val += ((fabs(consigne - tabT[i]) + fabs(consigne - tabT[i + 1])) / 2) * dt;
        }
        i_val *= 0.2;

        d_val = ((fabs(consigne - tabT[nT - 1]) - fabs(consigne - tabT[nT - 2])) / dt) * 0.15;
    }

    return p_val + i_val + d_val;
}
	 
float regulationTest(int regul,float consigne,float* tabT, int nT){
    float cmd = 0;

    if(regul == 1){
        cmd = regulation_TOR(consigne, tabT, nT);
    }
    else{
        cmd = regulation_PID(consigne, tabT, nT);
    }

    if(cmd > 100){
        cmd = 100;
    }
    if(cmd < 0){
        cmd = 0;
    }
		
	return cmd;
}
    
  
