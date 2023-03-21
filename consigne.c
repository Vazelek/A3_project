#include "consigne.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

float consigne(float thermostatPrec_f)
{
    float thermostat_f;
    /*FILE* ptr;
    char* cons[6];

    if (access(".verrouConsigne", F_OK) == 0) {
        thermostat_f=thermostatPrec_f;
    } else {
        FILE* fileptr = fopen(".verrouConsigne","wx");
        fclose(fileptr);
        ptr = fopen("consigne.txt", "r");
        if (NULL == ptr) {
            printf("file can't be opened \n");
        }
        fgets(cons, 6, ptr);
        thermostat_f = atof(cons);
        fclose(ptr);
        remove (".verrouConsigne");
    }
    return thermostat_f;*/

    if (access(".verrouConsigne", F_OK) == 0) { // file exists
        return thermostatPrec_f;
    }

    // Create file .verrouConsigne
    FILE* fileptr = fopen(".verrouConsigne","wx");
	if(fileptr == NULL)
	{
		perror("Error when creating .verrouConsigne file");
		return thermostatPrec_f;
	}
	fclose(fileptr); // close .verrouConsigne  (generate it)

    // read consigne.txt
    fileptr = fopen("consigne.txt","r");
	if(fileptr == NULL){
		perror("File consigne.txt does not exist");
		return thermostatPrec_f;
	}

    char str[6]; // longest string : "xx.xx\0"
    fscanf(fileptr, "%s", str);

    thermostat_f = atof(str);

    fclose(fileptr);

    remove(".verrouConsigne");

    return thermostat_f;
}