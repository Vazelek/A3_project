#include "releve.h"


FT_HANDLE init_usb(){
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    FT_STATUS ftStatus2;
    FT_STATUS ftStatus3;
    ftStatus = FT_Open(0, &ftHandle);
    if(ftStatus != FT_OK) {
        // FT_Open failed
        return NULL;
    }
    ftStatus = FT_SetBaudRate(ftHandle, 115200); // Set baud rate to 115200
    ftStatus2 = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE); // Set 8 data bits, 1 stop bit and no parity
    ftStatus3 = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0x11, 0x13); // No flow and 0x11 and 0x13 are useless
    if (ftStatus == FT_OK && ftStatus2 == FT_OK && ftStatus3 == FT_OK) {
        return ftHandle; // FT_SetBaudRate OK +  FT_SetDataCharacteristics OK + FT_SetFlowControl OK
    }
    else {
        return NULL; // FT_SetBaudRate Failed +-  FT_SetDataCharacteristics Failed +- FT_SetFlowControl Failed
    }
    FT_Close(ftHandle);
}

void read_temp(FT_HANDLE ftHandle){


    FT_STATUS ftStatus;
    DWORD EventDWord;
    DWORD TxBytes;
    DWORD RxBytes;
    DWORD BytesReceived;
    char RxBuffer[6];
    int tempInt = 0;
    int tempExt = 0;





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
            for (int i = 0; i < 6; ++i) {
                tempInt = RxBuffer[i];
                //printf("%x",RxBuffer[i]);
                printf("\n");
            }

        }

//        printf("combien de bytes lu : %ld\n",BytesReceived);
        for (int i = 0; i < 6; ++i) {
            printf("%x",RxBuffer[i]);
            printf("\n");
        }
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
}


