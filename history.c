#include "header.h"

void history_dis(char* ins)
{
    if(ins==NULL)
    {
        fseek(file,0,SEEK_END);
        int j=0;
        for(j=max(0,n_h-5);j<n_h;j++)
        {
            printf("%2d   %s",j+1,history[j]);
        }
    }
    else
    {
        int n = atoi(ins);
        if(n==0)
        {
            printf("Enter a valid number between 1 and 10\n");
            return;
        }
        if(n<=0 || n>10)
        {
            printf("Incorrect number of elements\n");
            return;
        }
        int j=0;
        for(j=max(0,n_h-n);j<n_h;j++)
        {
            printf("%2d %s",j+1,history[j]);
        }
    }    
}

void read_history()
{
    char name[100005];
    sprintf(name,"%s/.history.txt",INTDIR);
    file = fopen(name,"r");
    int  j=0;
    history[j] = malloc(1005*sizeof(char));
    if(history[j]==NULL)
    {
        printf("%sError in memory allocation%s\n",RED,NORMAL);
    }
    while(fgets(history[j],1000,file))
    {
        j++;
        history[j] = malloc(1005*sizeof(char));
    }
    n_h = j;
    fclose(file);
}

void write_history()
{
    char name[100005];
    sprintf(name,"%s/.history.txt",INTDIR);
    file = fopen(name,"w");
    if(file==NULL)
    {
        printf("%s Error in opening history file %s",RED,NORMAL);
        return;
    }
    int j=0;
    for(j=0;j<n_h;j++)
    {
        fprintf(file,"%s",history[j]);
    }
    fclose(file);
}