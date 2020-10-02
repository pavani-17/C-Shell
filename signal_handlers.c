#include "header.h"

void sigchld_handler(int signum) // Handles the signal received when the child process dies
{
    pid_t pid;
    int status1;
    if((pid=waitpid(-1,&status1, WNOHANG)) != -1) // Checks which process exited
    {
        int i;
        for(i=0;i<curr_proc;i++)
        {
            if(process_id[i] == pid)
            {
                fprintf(stderr,"\nProcess %s with Process ID %lld exited with exit code %d\n",process[i],process_id[i],status1);
                process_status[i] = 1;
            }
        }
    }
}

void sigint_handler(int signum)
{
    status = 0;
}

void sigtstp_handler(int signum)
{
    return;
}