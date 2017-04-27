#include "helper.h"

#define BUFFER 1000
#define FIRST_CPU_LINE 3
#define IDLE_INDEX 91 //SYS:35 USR:19 IDLE:91

float readFloatAtIndex(char* theString, int iIndex);
void refreshCPUdata(float *fCPU_Usage, float *fCpuCoresUsage, int *iNumberOfCore, bool *bRun);

int main(){
    int     i = 0;                  //
    int     iNumberOfCore = 0;      // number of core of the CPU
    float   fCPU_Usage;             //
    float   fCPU_Core_Usage[10];    // actual usage of each CPU's core
    bool    bRun = true;            //
    printf("Run. \n");

    //Create and launch CPU usage refresh thread
    std::thread CPURefreshThread(refreshCPUdata, &fCPU_Usage, fCPU_Core_Usage, &iNumberOfCore, &bRun);


    for(int iLoopTest = 0; iLoopTest<100; iLoopTest++) {
        usleep(500000);

        //just for debug
        printf("----------%i----------\n", i); i++;
        printf("there is %i core(s). \n", iNumberOfCore);
        printf("Total  : %f \n", fCPU_Usage);
        for (int iLoop = 0; iLoop < iNumberOfCore; iLoop++) {
            printf("Core %i : %f \n", iLoop, fCPU_Core_Usage[iLoop]);
        }
    }

    bRun = false;
    CPURefreshThread.join();
    printf("Stop. \n");
}

void refreshCPUdata(float *fCPU_Usage, float *fCpuCoresUsage, int *iNumberOfCore, bool *bRun){
    char buffer[BUFFER];    //reading buffer for command execution
    FILE * f;               //link to terminal
    int iCores;
    printf("Loop. \n");
    while(*bRun){
        //get current cpu usage via mpstat linux command
        f = popen( "mpstat -P ALL 1 1", "r" );

        //if not able to run command
        if ( f == 0 ) {
            fprintf( stderr, "Could not execute\n" );
        }else{
            iCores = 0;
            //go to first usefull line
            for(int iReadingLine=0; iReadingLine<FIRST_CPU_LINE; iReadingLine++){
                fgets( buffer, BUFFER,  f );
            }
            while( fgets( buffer, BUFFER, f)) {
                if(buffer[0]=='\n') break;      //end loop when reading is done

                    //else, if its the global usage line
                else if(buffer[13] == 'a' && buffer[14] == 'l' && buffer[15] == 'l'){
                    *fCPU_Usage = 100-readFloatAtIndex(buffer, IDLE_INDEX);                     //read the float value at the constant index for IDLE

                    //else, if its a core usage line
                }else if(buffer[15] == '0' + iCores){
                    
                    fCpuCoresUsage[iCores] = 100-readFloatAtIndex(buffer, IDLE_INDEX);  //read the float value at the constant index for IDLE
                    iCores += 1;                                                        //increment number of cores
                }
            }
            //closing terminal
            pclose(f);
        }
        *iNumberOfCore = iCores;
    }
    printf("End Loop. \n");
}
