#include "header.h"

void foreground(char **instruction, int len) // Execute the process in foreground 
{
    signal(SIGTTOU,SIG_IGN); // Ignore for changing terminal controlling process. Reset in both parent and child
    int fork_res = fork();
    setpgid(0,0); // Seperates both processes. Each one has their own process group
                  // Otherwise, no need to change terminal. However, bg might create issues as technically
                  // bg should not give terminal control
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
        // Has terminal control => Signals taken by it , hence signal handling is not needed in original shell for Ctrl-C and Z
        // Dont ignore it (Child inherits, so child also will ignore => Child wont stop or quit)  
        signal(SIGTTOU,SIG_DFL); // Default
        if(execvp(instruction[0],instruction)==-1)
        {
            fprintf(stderr,"No such command\n");
            exit(1);
        }
        status=0;
        exit(0);
    }
    else
    {
        int status1;
        curr_fore = fork_res;
        waitpid(fork_res,&status1,WUNTRACED); // Wait for child process 
                                              // Any signal, not necessarily stop

        tcsetpgrp(0,getpid());  // Take back control
        signal(SIGTTOU,SIG_DFL); // Default
        if(WIFSTOPPED(status1))
        {
            // Process sent SIGSTP
            // Ctrl-Z => Make it background, no need to suspend as it is already stopped

            // Put it in the array for track keeping
            process[curr_proc] = malloc(100 *sizeof(char));
            strcpy(process[curr_proc],instruction[0]);
            process_id[curr_proc] = fork_res;
            process_status[curr_proc] = 0;
            fprintf(stderr,"[%lld] %lld %s Suspended\n",curr_proc+1,process_id[curr_proc],process[curr_proc]);
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