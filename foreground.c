#include "header.h"

void foreground(char **instruction, int len) // Execute the process in foreground 
{
    signal(SIGTTOU,SIG_IGN);
    int fork_res = fork();
    setpgid(0,0);
    if(fork_res<0)
    {
        perror("New process");
        status=0;
        return;
    }
    if(fork_res==0)
    {
        instruction[len] = '\0';
        tcsetpgrp(0,getpid());
        signal(SIGTTOU,SIG_DFL);
        if(execvp(instruction[0],instruction)==-1)
        {
            perror(instruction[0]);
            exit(1);
        }
        status=0;
        exit(0);
    }
    else
    {
        int status1;
        curr_fore = fork_res;
        waitpid(fork_res,&status1,WUNTRACED);
        tcsetpgrp(0,getpid());
        signal(SIGTTOU,SIG_DFL);
        //printf("%d\n",status);
        if(WIFSTOPPED(status1))
        {
            //kill(curr_fore,SIGTSTP);
            //if(setpgid(curr_fore,0) < 0) perror("setpgid");
            process[curr_proc] = malloc(100 *sizeof(char));
            strcpy(process[curr_proc],instruction[0]);
            process_id[curr_proc] = fork_res;
            process_status[curr_proc] = 0;
            fprintf(stderr,"[%lld] %lld\n",curr_proc+1,process_id[curr_proc]);
            curr_proc++;
            status = 0;
            curr_fore = -1;
        }
        if(status1!=0)
        {
            status = 0;
        }
        
        curr_fore = -1;
        return;
    }
}