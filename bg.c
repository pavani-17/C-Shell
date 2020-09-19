#include "header.h"

void bg(char* pid)
{
    int pidt = atoi(pid);
    //printf("%d\n",pidt);
    if(pidt==0 || pidt > curr_proc || process_status[pidt-1]!=0)
    {
        printf("Incorrect process number \n");
        return;
    }
    kill(process_id[pidt-1],SIGCONT);

}