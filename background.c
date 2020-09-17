#include "header.h"

void sigchld_handler(int signum) // Handles the signal received when the child process dies
{
    pid_t pid;
    int status;
    if((pid=waitpid(-1,&status, WNOHANG)) != -1)
    {
        int i;
        for(i=0;i<curr_proc;i++)
        {
            if(process_id[i] == pid)
            {
                fprintf(stderr,"\nProcess %s with Process ID %lld exited with exit code %d\n",process[i],process_id[i],status);
                process_status[i] = 1;
            }
        }
    }
}

void background(char **instruction, int len) // Execute a process in bckground
{
    
    int fork_res = fork();  
    setpgid(0,0);  
    process[curr_proc] = malloc(100 *sizeof(char));
    if(process[curr_proc]==NULL)
    {
        printf("%s Error in assigning memory%s",RED,NORMAL);
        exit(0);
    }

    if(fork_res<0)
    {
        printf("Error in child process");
        return;
    }
    if(fork_res==0)
    {
        
        instruction[len] = '\0';
        if(execvp(instruction[0],instruction) < 0)
        {
            printf("Command not found\n");
            exit(0);
        }
        exit(0);
    }
    else
    {
        instruction[len] = '\0';
        strcpy(process[curr_proc],instruction[0]);
        process_id[curr_proc] = fork_res;
        process_status[curr_proc] = 0;
        printf("[%lld] %lld\n",curr_proc+1,process_id[curr_proc]);
        curr_proc++;
        return;
    }
}