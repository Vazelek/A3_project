#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "regulation.h"
    
float regulation_TOR(float consigne, float tint){
    if (consigne > tint){ // If tint < consigne, the heater should be ON
        return 50;
    }
    else{
        return 0;
    }
}

float regulation_PID(float consigne, float tint, float consigne_old, float tint_old, float *pid_i_old, unsigned char premier_echantillon){
    float dt = 10;
    float e = consigne - tint; // error
    // if(e <= 0){
    //     return 0;
    // }
    float p_val = e * 1.1; // Coef P value
    float i_val = 0; // Coef I value
    float d_val = 0; // Coef D value

    if(!premier_echantillon){ // If it is not the first iteration (if we have 2 values for tint and tint_old)
        // we calculate the air under the curve formed by the triangle
        // we make the average of the triangle which we multiply by dt in order to have a square
        // pid_i_old contain the sum of the air of all the precedent "squares"
        i_val = ((((consigne - tint) + (consigne_old - tint_old)) / 2) * dt) + *pid_i_old;
        *pid_i_old = i_val; // we update the total air under the curve
        i_val *= 0.2; // we multiply the total air by the coef Ki

        d_val = (((consigne - tint) - (consigne_old - tint_old)) / dt) * 0.15; // déplacement élémentaire sur un temps élémentaire : définition d'une dérivée
    }

    return p_val + i_val + d_val; // we return the sum of all coefs
}
	 
float regulation_Global(int regul, float consigne, float tint, float consigne_old, float tint_old, float *pid_i_old, unsigned char premier_echantillon){
    float cmd = 0;
    if(regul == 1){
        cmd = regulation_TOR(consigne, tint);
    }
    else{
        cmd = regulation_PID(consigne, tint, consigne_old, tint_old, pid_i_old, premier_echantillon);
    }

    if(cmd > 100){ // Saturation
        cmd = 100;
    }
    if(cmd < 0){
        cmd = 0;
    }
		
	return cmd;
}

float regulationTest(int regul, float consigne, float *tabT, int nT){
    float cmd = 0;
    float consigne_old = consigne; // previous instruction
    float tint_old = 0; // previous temperature
    float pid_i_old = 0; // previous total air under the curve (integral)


    for (int i = 0; i < nT; ++i)
    {
        if(i >= 1){ // First iteration : no old value
            tint_old = tabT[i - 1];
        }
        cmd = regulation_Global(regul, consigne, tabT[i], consigne_old, tint_old, &pid_i_old, (unsigned char) (i == 0));
    }

    return cmd;
}
    
  
