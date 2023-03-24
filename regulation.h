#ifndef REGULATION_H
#define REGULATION_H

#include <stdio.h>
#include <stdlib.h>
#include "define.h" 

float regulation_TOR(float consigne, float tint);
float regulation_PID(float consigne, float tint, float consigne_old, float tint_old, float *pid_i_old, unsigned char premier_echantillon);
float regulation_Global(int regul, float consigne, float tint, float consigne_old, float tint_old, float *pid_i_old, unsigned char premier_echantillon);
float regulationTest(int regul, float consigne, float *tabT, int nT);

#endif