#include "header.h"

void bg(char* pid)
{
    int pidt = atoi(pid);
    //printf("%d\n",pidt);
    if(pidt==0 || pidt > curr_proc || process_status[pidt-1]!=0)
    {
        fprintf(stderr,"Invalid process number \n");
        status = 1;
        return;
    }
    if(kill(process_id[pidt-1],SIGCONT)<0)
    {
        perror("kill");
        status = 0;
        return;
    }
}