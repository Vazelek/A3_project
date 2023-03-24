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
    fscanf(fileptr, "%s", str); // read first line true or false
    fscanf(fileptr, "%f", &temp_int); // read tempInt
    fscanf(fileptr, "%f", &temp_ext); // read tempExt
    fclose(fileptr);

    // write in data.txt
    fileptr = fopen("data.txt","w");
	if(fileptr == NULL){
		perror("File data.txt does not exist");
		return;
	}

    fprintf(fileptr, "%s\n", puissance_f ? "true" : "false"); // if pussance_f = 1 --> true else false
    fprintf(fileptr, "%.2f\n", temp_int); // write temp_int
    fprintf(fileptr, "%.2f\n", temp_ext); // write temp_ext
    
    fclose(fileptr);

    remove(".verrouData"); // delete file verrouData
}
