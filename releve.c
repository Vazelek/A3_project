#include "releve.h"

FT_STATUS read_temp(FT_HANDLE ftHandle, temp_t *temp){


    FT_STATUS ftStatus;
    DWORD EventDWord;
    DWORD TxBytes;
    DWORD RxBytes;
    DWORD BytesReceived;
    char RxBuffer[6];
    unsigned int tempIntSOT = 0;
    unsigned int tempExtSOT = 0;
    float tempInt = 0;
    float tempExt = 0;





    ftStatus = FT_GetStatus(ftHandle,&RxBytes,&TxBytes,&EventDWord);
    if (ftStatus == FT_OK) {
//        printf("premiere etape\n");
    }
//    printf("%d\n",RxBytes);
    if (RxBytes > 0) {

//        printf("deuxieme etape\n");
        ftStatus = FT_Read(ftHandle,RxBuffer,RxBytes,&BytesReceived);
        if (ftStatus == FT_OK) {
//            printf("ca lis\n");
<<<<<<< HEAD
            for (int i = 0; i < 6; ++i) {
                tempInt = RxBuffer[i];
                //printf("%x",RxBuffer[i]);
                printf("\n");
            }
=======
            tempExtSOT |= RxBuffer[0] & 0b1111;
            tempExtSOT |= (RxBuffer[1] & 0b1111) << 4;
            tempExtSOT |= (RxBuffer[2] & 0b1111) << 8;

            tempIntSOT |= RxBuffer[3] & 0b1111;
            tempIntSOT |= (RxBuffer[4] & 0b1111) << 4;
            tempIntSOT |= (RxBuffer[5] & 0b1111) << 8;

            tempExt = -39.64 + 0.04 * tempExtSOT;
            tempInt = -39.64 + 0.04 * tempIntSOT;

            temp->exterieure = tempExt;
            temp->interieure = tempInt;

//            printf("%x\n",tempIntSOT);
//            for (int i = 0; i < 6; ++i) {
//                tempIntSOT |= RxBuffer[i] & 0b1111;
//                printf("%x",RxBuffer[i]);
//                printf("\n");
//            }


>>>>>>> a44533b (releve working)

        }

//        printf("combien de bytes lu : %ld\n",BytesReceived);
//        for (int i = 0; i < 6; ++i) {
//            printf("%x",RxBuffer[i]);
//            printf("\n");
//        }
/*
            for (int i = 1; i < 2; ++i) {
                printf("%x",RxBuffer[i]);
            }
            printf("\n");
            for (int i = 2; i < 3; ++i) {
                printf("%x",RxBuffer[i]);
            }
            printf("\n");
            for (int i = 3; i < 4; ++i) {
                printf("%x",RxBuffer[i]);
            }
            printf("\n");
*/
    }

/*
    FT_STATUS ftStatus;
    DWORD RxBytes;
    DWORD TxBytes;
    DWORD BytesReceived;
    DWORD EventDWord;
    unsigned int SOT_ext = 0;
    unsigned int SOT_int = 0;

    // Vérification de la disponibilité de données
    ftStatus = FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord);

    // Si des données sont disponibles à la lecture
    if (ftStatus == FT_OK && RxBytes > 0)
    {
        printf("fezezfgfyezhjfezhjfez\n");
    }
    */
//    FT_Close(ftHandle);
    return ftStatus;
}


