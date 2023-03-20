#include "visualisationT.h"
#include <unistd.h>
#include <stdio.h>

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

    char str[20];
    unsigned short int temoin;
    fgets(str, 20, fileptr);
    temoin = (strcmp(str, "true"));
    print(temoin);
    fgets(str, 20, fileptr);
    printf("%s/", str);
    fgets(str, 20, fileptr);
    printf("%s/", str);



    remove(".verrouData");

}

int main(){
    temp_t myTemp;
    myTemp.exterieure = 15.0;
    myTemp.interieure = 20.0;
    visualisationT(myTemp);
    return 0;
}