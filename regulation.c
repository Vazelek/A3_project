#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "regulation.h"

// float regulation_TOR(float consigne, float* tabT, int nT){
//     if (consigne > tabT[nT-1]){
//         return 50;
//     }
//     else{
//         return 0;
//     }
// }

// float regulation_PID(float consigne, float* tabT, int nT){
//     float dt = 10;
//     float e = consigne - tabT[nT - 1];
//     if(e <= 0){
//         return 0;
//     }
//     float p_val = e * 1.1;
//     float i_val = 0;
//     float d_val = 0;

//     if(nT > 1){
//         for(int i = 0; i < nT - 1; i++){
//             i_val += ((fabs(consigne - tabT[i]) + fabs(consigne - tabT[i + 1])) / 2) * dt;
//         }
//         i_val *= 0.2;

//         d_val = ((fabs(consigne - tabT[nT - 1]) - fabs(consigne - tabT[nT - 2])) / dt) * 0.15;
//     }

//     return p_val + i_val + d_val;
// }
	 
// float regulationTest(int regul,float consigne,float* tabT, int nT){
//     float cmd = 0;

//     if(regul == 1){
//         cmd = regulation_TOR(consigne, tabT, nT);
//     }
//     else{
//         cmd = regulation_PID(consigne, tabT, nT);
//     }

//     if(cmd > 100){
//         cmd = 100;
//     }
//     if(cmd < 0){
//         cmd = 0;
//     }
		
// 	return cmd;
// }
    
float regulation_TOR(float consigne, float tint){
    if (consigne > tint){
        return 50;
    }
    else{
        return 0;
    }
}

float regulation_PID(float consigne, float tint, float consigne_old, float tint_old, float *pid_i_old, unsigned char premier_echantillon){
    float dt = 10;
    float e = consigne - tint;
    if(e <= 0){
        return 0;
    }
    float p_val = e * 1.1;
    float i_val = 0;
    float d_val = 0;

    if(!premier_echantillon){
        i_val = (((fabs(consigne - tint) + fabs(consigne_old - tint_old)) / 2) * dt) + *pid_i_old;
        *pid_i_old = i_val;
        i_val *= 0.2;

        d_val = ((fabs(consigne - tint) - fabs(consigne_old - tint_old)) / dt) * 0.15;
    }

    return p_val + i_val + d_val;
}
	 
float regulation_Global(int regul, float consigne, float tint, float consigne_old, float tint_old, float *pid_i_old, unsigned char premier_echantillon){
    float cmd = 0;
    float fpid = *pid_i_old;
    if(regul == 1){
        cmd = regulation_TOR(consigne, tint);
    }
    else{
        cmd = regulation_PID(consigne, tint, consigne_old, tint_old, pid_i_old, premier_echantillon);
    }

    if(cmd > 100){
        cmd = 100;
    }
    if(cmd < 0){
        cmd = 0;
    }


    /*if(*pid_i_old != fpid){
        printf("Good : %f / %f\n", *pid_i_old, fpid);
    }
    {
        printf("notgood\n");
    }*/
    //printf("Erreur = %f - %f = %f", tint, consigne, cmd);
		
	return cmd;
}

float regulationTest(int regul, float consigne, float *tabT, int nT){
    float cmd = 0;
    float consigne_old = consigne;
    float tint_old = 0;
    float pid_i_old = 0;


    for (int i = 0; i < nT; ++i)
    {
        if(i >= 1){
            tint_old = tabT[i - 1];
        }
        cmd = regulation_Global(regul, consigne, tabT[i], consigne_old, tint_old, &pid_i_old, (unsigned char) (i == 0));
    }

    return cmd;
}
    
  
