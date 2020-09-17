#include "header.h"

void get_input() // Read input from the browser
{
    char* buffer;
    size_t bufsize = 100005;
    buffer = (char *)malloc(bufsize * sizeof(char));
    if(buffer==NULL)
    {
        printf("%s Error in assigning memory%s",RED,NORMAL);
        exit(0);
    }
    
    getline(&buffer,&bufsize,stdin);
    history[n_h] = malloc(100000*sizeof(char)); 
    if(history[n_h]==NULL)
    {
        printf("%s Error in memory alloaction %s",RED,NORMAL);
        exit(0);
    }
    if(n_h!=0)
    {
        if(strcmp(history[n_h-1],buffer)==0)
        {
            process_input(buffer);
            return;
        }
    }
    if(n_h<20)
    {
        strcpy(history[n_h],buffer);
        n_h++;
    }
    else
    {
        strcpy(history[n_h],buffer);
        n_h++;
        char name[100005];
        sprintf(name,"%s/.history.txt",INTDIR);
        remove(name);
        int j;
        for(j=1;j<n_h;j++)
        {
            history[j-1] = history[j];
        }
        n_h--;
    }
    write_history();
    process_input(buffer);
    free(buffer);
}

void process_input(char* input) // Seperate the inputs on basis of ';'
{
    char* tok; 

    tok = strtok(input, ";");
    int i = 0;

    while(tok!=NULL)
    {
        processPipe(tok);
        tok = strtok(0,";");
    }   
}

void execute_input(char* instructions) // Execute input
{
    int j=0,k;
    char* tok;
    char** sin_ins = malloc(10000*sizeof(char *));
    if(sin_ins==NULL)
    {
        printf("%s Error in assigning memory%s",RED,NORMAL);
        exit(0);
    }
    tok = strtok(instructions," \t");
    k=0;
    while(tok!=NULL)
    {
        sin_ins[k] = tok;
        k++;
        tok = strtok(0," ");
    }
    execute_inst(sin_ins,k);
    j++;
    free(sin_ins);
}