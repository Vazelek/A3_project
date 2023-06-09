#ifndef SIMULATEUR_H
#define SIMULATEUR_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "define.h"

struct simParam_s{
   float tempInt_f;
   float tempExt_f;
   FILE* trace_pf;
   float rgf;
   float kr;
   long int compteur_i;
};

struct simParam_s* simConstruct(temp_t temperature);
temp_t simCalc(float puissance, struct simParam_s* param_ps);
void simDestruct(struct simParam_s* param_ps);
#endif

