#include "header.h"

void sigchld_handler(int signum)
{
    pid_t pid;
    int status;
    while((pid=waitpid(-1,&status, WNOHANG)) != -1)
    {
        printf("Process with PID %d exitted with status %d\n",pid,status);
    }
}

void background(char **instruction, int len)
{
    
    int fork_res = fork();
    if(fork_res==0)
    {
        instruction[len] = '\0';
        printf("%d\n",getpid());
        execvp(instruction[0],instruction);
        exit(0);
    }
    else
    {
        return;
    }
}