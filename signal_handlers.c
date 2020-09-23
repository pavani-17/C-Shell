#include "header.h"

void sigchld_handler(int signum) // Handles the signal received when the child process dies
{
    pid_t pid;
    int status1;
    if((pid=waitpid(-1,&status1, WNOHANG)) != -1)
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
    if(curr_fore!=-1)
    {
        kill(curr_fore,9);
        curr_fore = -1;
    }
    else
    {
        return;
    }
    status = 0;
}

void sigtstp_handler(int signum)
{
    if(curr_fore != -1)
    {
        process[curr_proc] = malloc(100005*sizeof(char));
        strcpy(process[curr_proc],curr_fore_proc);
        process_id[curr_proc] = curr_fore;
        process_status[curr_proc] = 0;
        printf("[%lld] %lld\n",curr_proc+1,process_id[curr_proc]);
        curr_proc++;
        status = 0;
    }
    return;
}