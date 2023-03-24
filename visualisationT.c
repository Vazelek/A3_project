#include "visualisationT.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void visualisationT(temp_t myTemp)
{
    if (access(".verrouData", F_OK) == 0) { // file verrouData exists
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
    unsigned short int temoin = 0;
    fscanf(fileptr, "%s", str);  // read first line : true or false
    temoin = (strcmp(str, "true") == 0); // strcmp = 0 if str == "true\n"
    
    fclose(fileptr);

    //write in data.txt
    fileptr = fopen("data.txt","w");
	if(fileptr == NULL){
		perror("File data.txt does not exist");
		return;
	}

    fprintf(fileptr, "%s\n", temoin ? "true" : "false"); // if pussance_f = 1 --> true else false
    fprintf(fileptr, "%.2f\n", myTemp.interieure); // copy tempInt
    fprintf(fileptr, "%.2f\n", myTemp.exterieure); // copy tempExt
    
    fclose(fileptr);


    remove(".verrouData"); // delete file verrouData

}