#include "header.h"

void foreground(char **instruction, int len)
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
        wait(NULL);
        return;
    }
}