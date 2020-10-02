#include "header.h"

void processPipe(char* input)
{
    // Basic Idea
    // Create an array of pipes
    // n processes => n pipes (n-1 used)
    // Pipe input of one to ouput of the other
    // Output of last is piped to cout
    // Important => Pipe wont read until all write ends are closed
    // Didnt create child process (Can create, no difference, MUST CLOSE IN BOTH PROCESSES)
    char** instructions = malloc(1000*sizeof(char));
    int i=0;
    char* tok = strtok(input,"|");
    while(tok!=NULL)
    {
        instructions[i] = malloc(100000*sizeof(char));
        instructions[i] = tok;
        i++;
        tok = strtok(NULL,"|");
    }
    int j;
    int cin_temp = dup(0); // Copy of cin
    int cout_temp = dup(1); // Copy of cout
    int fd[i][2];

    for(j=0;j<i;j++)
    {
        if(j==(i-1))
        {
            dup2(cout_temp,1); // Last output is set to cout
            output_redirection(instructions[j]);
            dup2(cin_temp,0);
            if((j-1)!=0)
            {
                close(fd[j-1][0]);
            }
        }
        else
        {
            if(pipe(fd[j]) < 0)
            {
                perror("Pipe creation");
                status = 0;
                break;
            }
            dup2(fd[j][1],1);
            output_redirection(instructions[j]);
            close(fd[j][1]);
            dup2(fd[j][0],0);
            if(j!=0)
            {
                close(fd[j-1][0]);
            }
        } 
    }
    dup2(cout_temp,1);
    dup2(cin_temp,0);
}