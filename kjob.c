#include "header.h"

void kjob(char* pid, char* sig_id) // Send signal based on job_id
{
    int pid_v = atoi(pid);
    int sig_idv = atoi(sig_id);
    if(curr_proc < pid_v)
    {
        fprintf(stderr,"Incorrect Process ID\n");
        status=0;
        return;
    }
    if(kill(process_id[pid_v-1],sig_idv)<0)
    {
        perror("kjob ");
        status=0;
        return;
    }
    return;
}