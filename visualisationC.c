#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "visualisationC.h"

void visualisationC(float puissance_f)
{
    if (access(".verrouData", F_OK) == 0) { // file exists
        return;
    }

    // Create file .verrouData
    FILE* fileptr = fopen(".verrouData","wx");
	if(fileptr == NULL)
	{
		perror("Error when creating .verrouData file");
		return;
	}
	fclose(fileptr); // close .verrouData  (generate it)

    // read data.txt
    fileptr = fopen("data.txt","r");
	if(fileptr == NULL){
		perror("File data.txt does not exist");
		return;
	}

    char str[6]; // longest string : "false\0"
    float temp_int;
    float temp_ext;
    fscanf(fileptr, "%s", str);
    fscanf(fileptr, "%f", &temp_int);
    fscanf(fileptr, "%f", &temp_ext);
    fclose(fileptr);

    fileptr = fopen("data.txt","w");
	if(fileptr == NULL){
		perror("File data.txt does not exist");
		return;
	}

    fprintf(fileptr, "%s\n", puissance_f ? "true" : "false");
    fprintf(fileptr, "%.2f\n", temp_int);
    fprintf(fileptr, "%.2f\n", temp_ext);
    
    fclose(fileptr);

    remove(".verrouData");
}
