#include "header.h"

void sigchld_handler(int signum)
{
    pid_t pid;
    int status;
    while((pid=waitpid(-1,&status, WNOHANG)) != -1)
    {
        int i;
        for(i=0;i<curr_proc;i++)
        {
            if(process_id[i] == pid)
            {
                printf("\nProcess %s with Process ID %d exited with exit code %d\n",process[i],process_id[i],status);
                free(process[i]);
            }
        }
    }
}

void background(char **instruction, int len)
{
    
    int fork_res = fork();    
    process[curr_proc] = malloc(100 *sizeof(char));
    if(process[curr_proc]==NULL)
    {
        printf("%s Error in assigning memory%s",RED,NORMAL);
        exit(0);
    }
    if(fork_res==0)
    {
        instruction[len] = '\0';
        execvp(instruction[0],instruction);
        exit(0);
    }
    else
    {
        instruction[len] = '\0';
        strcpy(process[curr_proc],instruction[0]);
        process_id[curr_proc] = fork_res;
        printf("[%d] %d\n",curr_proc+1,process_id[curr_proc]);
        curr_proc++;
        return;
    }
}