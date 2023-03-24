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





    ftStatus = FT_GetStatus(ftHandle,&RxBytes,&TxBytes,&EventDWord);
    if (ftStatus == FT_OK) {
        printf("premiere etape\n");
    }

    if (RxBytes > 0) {
        printf("deuxieme etape\n");
        ftStatus = FT_Read(ftHandle,RxBuffer,6,&BytesReceived);
        if (ftStatus == FT_OK) {
            printf("ca lis\n");
        }

        printf("combien de bytes lu : %ld\n",BytesReceived);
        for (int i = 0; i < 5; ++i) {
            printf("%x",RxBuffer[i]);
            printf("\n");
        }

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

    }
    FT_Close(ftHandle);
}


