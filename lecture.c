#include <stdio.h>
#include <stdlib.h>
#include "ftd2xx.h"
#include "lecture.h"

void lecture(){
    FT_HANDLE ftHandle; 
    FT_STATUS ftStatus; 
    DWORD EventDWord;
    DWORD RxBytes;
    DWORD TxBytes;  
    DWORD BytesReceived; 
    unsigned char RxBuffer[256];
    ftStatus = FT_Open(0, &ftHandle);
    printf("open lecture\n");
    if(ftStatus != FT_OK) { 
        // FT_Open failed
        printf("open failed\n");
        return; 
    }
    ftStatus = FT_SetBaudRate(ftHandle, FT_BAUD_460800);
    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
    FT_GetStatus(ftHandle,&RxBytes,&TxBytes,&EventDWord);
    if (RxBytes > 0) {
        ftStatus = FT_Read(ftHandle,RxBuffer,RxBytes,&BytesReceived); 
        if (ftStatus == FT_OK) { 
            // FT_Read OK
            printf("read OK\n");
            printf("RxBytes: %d\n",RxBytes);
            printf("RxBuffer: %s\n",RxBuffer);
            printf("BytesReceived: %d\n",BytesReceived);
        } 
        else { 
            // FT_Read failed
            printf("read failed\n");
        } 
    }
    else{
        printf("no data\n");
    }
    FT_Close(ftHandle); 
}
