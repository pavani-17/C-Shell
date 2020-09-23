#include "header.h"

void fg(char* pid)
{
    int pidt = atoi(pid);
    //printf("%d\n",pidt);
    if(pidt==0 || pidt > curr_proc || process_status[pidt-1]!=0)
    {
        fprintf(stderr,"Incorrect process number \n");
        status = 0;
    }
    else
    {
        //printf("Came here\n");
        // if(setpgid(process_id[pidt-1],0)<0)
        // {
        //     perror("setpgid");
        // }
        kill(process_id[pidt-1],SIGCONT);
        // int status;
        // waitpid(process_id[pidt-1],&status,WUNTRACED);
        int status;
        int shellpid = getpgid(0);
        signal(SIGTTOU, SIG_IGN);
        tcsetpgrp(0,getpgid(process_id[pidt-1]));
        //signal(SIGTTOU, SIG_DFL);
        waitpid(process_id[pidt-1],&status,WUNTRACED);
        //signal(SIGTTOU, SIG_IGN);
        tcsetpgrp(0,shellpid);
        signal(SIGTTOU, SIG_DFL);
        return;
    }
}