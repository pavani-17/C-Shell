#include "header.h"

void fg(char* pid)
{
    int pidt = atoi(pid);
    if(pidt==0 || pidt > curr_proc || process_status[pidt-1]==0)
    {
        printf("Incorrect process number \n");
    }
    else
    {
        kill(process_id[pidt-1],SIGCONT);
        tcsetpgrp(0,process_id[pidt-1]);
    }
}