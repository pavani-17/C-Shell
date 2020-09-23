#include "header.h"

void background(char **instruction, int len) // Execute a process in bckground
{
    
    int fork_res = fork();  
    setpgid(0,0);  
    process[curr_proc] = malloc(100 *sizeof(char));
    if(process[curr_proc]==NULL)
    {
        fprintf(stderr,"Error in assigning memory");
        exit(0);
    }

    if(fork_res<0)
    {
        perror("New process");
        status=1;
        return;
    }
    if(fork_res==0)
    {
        
        instruction[len] = '\0';
        if(execvp(instruction[0],instruction) < 0)
        {
            fprintf(stderr,"Command not found\n");
            exit(1);
        }
        exit(0);
    }
    else
    {
        instruction[len] = '\0';
        strcpy(process[curr_proc],instruction[0]);
        process_id[curr_proc] = fork_res;
        process_status[curr_proc] = 0;
        fprintf(stderr,"[%lld] %lld\n",curr_proc+1,process_id[curr_proc]);
        curr_proc++;
        return;
    }
}