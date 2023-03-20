#ifndef REGULATION_H
#define REGULATION_H

#include <stdio.h>
#include <stdlib.h>
#include "define.h" 

float regulation_TOR(float consigne, float* tabT, int nT);
float regulation_PID(float consigne, float* tabT, int nT);
float regulationTest(int regul,float consigne,float* tabT, int nT);

#endif