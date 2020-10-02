#include "header.h"

void bg(char* pid) // Changes state to running from stopped for a background process
{
    // Does not work for terminal controlling processes such as vim,nano etc
    // Wont stop if given for ping, only option = Ctrl-D
    int pidt = atoi(pid);
    if(pidt==0 || pidt > curr_proc || process_status[pidt-1]!=0)
    {
        fprintf(stderr,"Invalid process number \n");
        status = 1;
        return;
    }
    if(kill(process_id[pidt-1],SIGCONT)<0) // Send signal
    {
        perror("kill");
        status = 0;
        return;
    }
}