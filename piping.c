#include "header.h"

void processPipe(char* input)
{
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
    // for(j=0;j<i;j++)
    // {
    //     printf("%s %d\n",instructions[j],j);
    // }
    int cin_temp = dup(0);
    int cout_temp = dup(1);
    int fd[i][2];
    // printf("%d\n",i);
    for(j=0;j<i;j++)
    {
        //printf("%s\n",instructions[j]);
        if(j==(i-1))
        {
            dup2(cout_temp,1);
            //printf("Recognise   %s\n",instructions[j]);
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
            }
            //printf("Or dont %s\n",instructions[j]);
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