#include "header.h"

void foreground(char **instruction, int len)
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
            printf("Command not found");
        }
        exit(0);
    }
    else
    {
        int status;
        if(waitpid(fork_res,NULL,WUNTRACED )==-1)
        {
            printf("%s Error in child process %s",RED,NORMAL);
            exit(0);
        }
        return;
    }
}