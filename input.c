#include "header.h"

void get_input() // Read input from the browser
{
    char* buffer;
    size_t bufsize = 100005;
    buffer = (char *)malloc(bufsize * sizeof(char));
    if(buffer==NULL)
    {
       fprintf(stderr," Error in assigning memory\n");
        exit(0);
    }
    
    int p = getline(&buffer,&bufsize,stdin);
    if(p==-1)
    {
        printf("\n");
        quit();
    }
    long long int len = strlen(buffer);
    long long int i = 0;
    int flag=0;
    for(i=0;i<len;i++)
    {
        if(buffer[i]!='\n' && buffer[i]!=' ' && buffer[i]!='\t')
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        status=0;
        return;
    }
    history[n_h] = malloc(100000*sizeof(char)); 
    if(history[n_h]==NULL)
    {
        fprintf(stderr," Error in memory alloaction \n");
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
    tok = strsep(&input, ";\n");
    int i = 0;

    while(tok!=NULL)
    {
        chaining(tok);
        tok = strsep(&input,";\n");        
    }   
}

void execute_input(char* instructions) // Execute input
{
    int j=0,k;
    char* tok;
    char** sin_ins = malloc(10000*sizeof(char *));
    if(sin_ins==NULL)
    {
        fprintf(stderr," Error in assigning memory\n");
        exit(0);
    }

    tok = strtok(instructions," \t\n");
    if(tok==NULL)
    {
        status = 0;
        return;
    }
    k=0;
    while(tok!=NULL)
    {
        sin_ins[k] = malloc(100005*sizeof(char));
        strcpy(sin_ins[k],tok);
        k++;
        tok = strtok(0," \t\n");
    }
    execute_inst(sin_ins,k);
    j++;
    free(sin_ins);
}