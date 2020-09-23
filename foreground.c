#include "header.h"

void foreground(char **instruction, int len) // Execute the process in foreground 
{
    int fork_res = fork();
    if(fork_res<0)
    {
        perror("New process");
        status=0;
        return;
    }
    if(fork_res==0)
    {
        instruction[len] = '\0';
        if(execvp(instruction[0],instruction)==-1)
        {
            fprintf(stderr,"Command not found\n");
            exit(1);
        }
        status=0;
        exit(0);
    }
    else
    {
        int status1;
        strcpy(curr_fore_proc,instruction[0]);
        curr_fore = fork_res;
        waitpid(fork_res,&status1,WUNTRACED);
        //printf("%d\n",status);
        if(status1!=0)
        {
            status = 0;
        }
        
        curr_fore = -1;
        return;
    }
}