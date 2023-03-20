#include "consigne.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

float consigne(float thermostatPrec_f)
{
    float thermostat_f;
    FILE* ptr;
    char * cons = (char *) malloc( 4 );
    if (access(".verrouConsigne", F_OK) == 0) {
        thermostat_f=thermostatPrec_f;
    } else {
        fopen (".verrouConsigne", "r");
        ptr = fopen("consigne.txt", "r");
        if (NULL == ptr) {
            printf("file can't be opened \n");
        }
        fgets(cons, 4, ptr);
        thermostat_f = atoll(cons);
        remove (".verrouConsigne");
    }
    return thermostat_f;

}


