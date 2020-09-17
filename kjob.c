#include "header.h"

void kjob(char* pid, char* sig_id)
{
    int pid_v = atoi(pid);
    int sig_idv = atoi(sig_id);
    if(curr_proc < pid_v)
    {
        printf("Incorrect Process ID\n");
        return;
    }
    if(kill(process_id[pid_v-1],sig_idv)<0)
    {
        perror("kjob ");
    }
    return;
}