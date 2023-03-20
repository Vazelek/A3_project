#include "visualisationT.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void visualisationT(temp_t myTemp)
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

    char str[8]; // longest string : "false\r\n\0"
    unsigned short int temoin = 0;
    fgets(str, 8, fileptr);
    temoin = (strcmp(str, "true\r\n") == 0); // strcmp = 0 if str == "true\n"
    printf("%s\n", temoin ? "true" : "false");
    printf("%d\n", temoin);
    fgets(str, 8, fileptr);
    myTemp.interieure = atof(str);
    printf("%f\n", myTemp.interieure);
    fgets(str, 8, fileptr);
    myTemp.exterieure = atof(str);
    printf("%f\n", myTemp.exterieure);

    fclose(fileptr);

    remove(".verrouData");

}
/*
int main(){
    temp_t myTemp;
    myTemp.exterieure = 15.0;
    myTemp.interieure = 20.0;
    visualisationT(myTemp);
    return 0;
}
 */