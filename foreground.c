#include "header.h"

void foreground(char **instruction, int len) // Execute the process in foreground 
{
    int fork_res = fork();
    if(fork_res<0)
    {
        perror("New process");
    }
    if(fork_res==0)
    {
        instruction[len] = '\0';
        if(execvp(instruction[0],instruction)==-1)
        {
            printf("Command not found\n");
        }
        exit(0);
    }
    else
    {
        int status;
        waitpid(fork_res,&status,WUNTRACED );
        return;
    }
}