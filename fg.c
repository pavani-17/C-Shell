#include "header.h"

void fg(char* pid)
{
    useconds_t t = 1000;
    usleep(t);
    // Prevents race conditions (Otherwise vim &; fg 1 might enter a race condition)
    int pidt = atoi(pid);
    if(pidt<=0 || pidt > curr_proc || process_status[pidt-1]!=0)
    {
        fprintf(stderr,"Invalid process number \n");
        status = 0;
    }
    else
    {
        // Basic Idea
        // Ignore SIGTTOU (SIGTTIN is not needed) to enable terminal controlling
        // Send SIGCONT signal
        // Give the process terminal control (tscetpgrp)
        // Wait for it
        // After getting signal, check if it was stopped again (Using Ctrl-Z). If yes, print appropriate message
        // Warning : waitpid waits for any signal (Not only killing one)
        // => Creates synchronisation issues and race conditions 
        fprintf(stderr,"[%d] %lld %s Resumed\n",pidt,process_id[pidt-1],process[pidt-1]);
        int status1;
        int shellpid = getpgid(0);
        signal(SIGTTOU, SIG_IGN); // Default behavior is to suspend terminal requesting process
        kill(process_id[pidt-1],SIGCONT);
        tcsetpgrp(0,getpgid(process_id[pidt-1]));
        //signal(SIGTTOU, SIG_DFL);  => Not needed 
        waitpid(process_id[pidt-1],&status1,WUNTRACED);
        //signal(SIGTTOU, SIG_IGN); => Not needed 
        tcsetpgrp(0,shellpid); // take shell back 
        signal(SIGTTOU, SIG_DFL); // Reset
        if(WIFSTOPPED(status1))
        {
            fprintf(stderr,"[%d] %lld %s Suspended\n",pidt,process_id[pidt-1],process[pidt-1]);
        }
        return;
    }
}