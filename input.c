#include "header.h"

void get_input()
{
    char* buffer;
    size_t bufsize = 100005;
    buffer = (char *)malloc(bufsize * sizeof(char));
    getline(&buffer,&bufsize,stdin);
    process_input(buffer);
}

void process_input(char* input)
{
    char **tokens = malloc(10000*sizeof(char*));
    char* tok; 

    tok = strtok(input, ";");
    int i = 0;

    while(tok!=NULL)
    {
        tokens[i] = tok;
        tok = strtok(0,";");
        i++;
    }   
    execute_input(tokens, i);
}

void execute_input(char** instructions, int num_ins)
{
    int j=0,k;
    char* tok;
    char** sin_ins = malloc(10000*sizeof(char *));

    while(j<num_ins)
    {
        tok = strtok(instructions[j]," ");
        k=0;
        while(tok!=NULL)
        {
            sin_ins[k] = tok;
            k++;
            tok = strtok(0," ");
        }
        execute_inst(sin_ins,k);
        j++;
    }

}