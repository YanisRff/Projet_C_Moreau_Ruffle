#include "lecture.h"
absorp lecture(float *time){
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    FT_STATUS ftStatus;
    DWORD numDevs;
    char *BufPtrs[3];  
    char Buffer1[64];  
    char Buffer2[64];  
    BufPtrs[0] = Buffer1; 
    BufPtrs[1] = Buffer2; 
    BufPtrs[2] = NULL; 
    ftStatus = FT_ListDevices(BufPtrs,&numDevs,FT_LIST_ALL|FT_OPEN_BY_SERIAL_NUMBER);  
    if (ftStatus == FT_OK) {
        //printf("Device 0: %s\n",Buffer1);
    }

    ftStatus = FT_SetVIDPID(0403,6015);
    if (ftStatus == FT_OK) {
        //printf("VID and PID set\n");
    }

    FT_HANDLE ftHandle; 
    DWORD EventDWord;
    DWORD RxBytes;
    DWORD TxBytes;  
    DWORD BytesReceived; 
    unsigned char RxBuffer[256];
    ftStatus = FT_OpenEx((PVOID) Buffer1,FT_OPEN_BY_SERIAL_NUMBER,&ftHandle);
    //ftStatus = FT_Open(0,&ftHandle);
    //printf("open lecture\n");
    if(ftStatus != FT_OK) { 
        // FT_Open failed
        printf("open failed\n");
    }
    ftStatus |= FT_SetBaudRate(ftHandle, FT_BAUD_460800);
    ftStatus |= FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
    if(ftStatus != FT_OK) { 
        // FT_SetBaudRate or FT_SetDataCharacteristics failed
        printf("set failed\n");
    }
    int i = 0; 
    int etat = 0;
    int count = 0;
    char info[20];
    while(i < 1){
    FT_GetStatus(ftHandle,&RxBytes,&TxBytes,&EventDWord);
    if (RxBytes > 0) {
        ftStatus = FT_Read(ftHandle,RxBuffer,RxBytes,&BytesReceived); 
        if (ftStatus == FT_OK) { 
            // FT_Read OK
            //printf("read ok\n");
            for(int j = 0; j < sizeof(RxBuffer); j++){
                if (RxBuffer[j] == '\n' && etat == 0){
                    etat = 1;
                    count = 0;
                }
                if (RxBuffer[j] == '\r' && etat == 1){
                    etat = 0;
                    if (count >= 20){
                        break;
                    }
                    else{
                        count = 0;
                    }
                }
                if (etat == 1){
                    info[count] = RxBuffer[j];
                    count++;
                }
            }

            i++;
        } 
        else { 
            // FT_Read failed
            printf("read failed\n");
        } 
    }
    }
    FT_Close(ftHandle);

    int char_to_int(char c) {
        return (c - '0');
    }

    float acr = char_to_int(info[1])*1000 + char_to_int(info[2])*100 + char_to_int(info[3])*10 + char_to_int(info[4]) - 2000;
    float dcr = char_to_int(info[6])*1000 + char_to_int(info[7])*100 + char_to_int(info[8])*10 + char_to_int(info[9]) - 2000;
    float acir = char_to_int(info[11])*1000 + char_to_int(info[12])*100 + char_to_int(info[13])*10 + char_to_int(info[14])-2000;
    float dcir = char_to_int(info[16])*1000 + char_to_int(info[17])*100 + char_to_int(info[18])*10 + char_to_int(info[19]) - 2000;
    
    printf("lecture\n");
    printf("acr : %f\n", acr);
    printf("dcr : %f\n", dcr);
    printf("acir : %f\n", acir);
    printf("dcir : %f\n", dcir);
    printf("\n");

    absorp myAbsorp;
    myAbsorp.acr = acr;
    myAbsorp.dcr = dcr;
    myAbsorp.acir = acir;
    myAbsorp.dcir = dcir;

    end = clock();
    cpu_time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
    //printf("temps : %f\n", cpu_time_used);
    *time = cpu_time_used;
    //printf("temps : %f\n", *time);

    return myAbsorp;

}
