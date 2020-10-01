#include "header.h"

void history_dis(char* ins) // Print history 
{
    if(ins==NULL)
    {
        int j=0;
        for(j=max(0,n_h-10);j<n_h;j++)
        {
            printf("%2d   %s",j+1,history[j]);
        }
    }
    else
    {
        int n = atoi(ins);
        if(n==0)
        {
            fprintf(stderr,"Enter a valid number between 1 and 20\n");
            status = 0;
            return;
        }
        if(n<=0 || n>20)
        {
            fprintf(stderr,"Incorrect number of elements\n");
            status = 0;
            return;
        }
        int j=0;
        for(j=max(0,n_h-n);j<n_h;j++)
        {
            printf("%2d %s",j+1,history[j]);
        }
    }    
}

void read_history() // Read history from file
{
    char name[100005];
    sprintf(name,"%s/.history.txt",INTDIR);
    FILE* file;
    file = fopen(name,"r");
    int  j=0;
    history[j] = malloc(1005*sizeof(char));
    if(history[j]==NULL)
    {
        fprintf(stderr,"%sError in memory allocation%s\n",RED,NORMAL);
        return;
    }
    while(fgets(history[j],1000,file))
    {
        j++;
        history[j] = malloc(1005*sizeof(char));
    }
    n_h = j;
    fclose(file);
}

void write_history() // Write history for the file
{
    char name[100005];
    sprintf(name,"%s/.history.txt",INTDIR);
    FILE* file;
    file = fopen(name,"w");
    if(file==NULL)
    {
        perror("History");
        return;
    }
    int j=0;
    for(j=0;j<n_h;j++)
    {
        
    }
    for(j=0;j<n_h;j++)
    {
        fprintf(file,"%s",history[j]);
    }
    fclose(file);
}