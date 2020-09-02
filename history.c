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
    file = fopen(".history.txt","r");
    int  j=0;
    history[j] = malloc(1005*sizeof(char));
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
    file = fopen(".history.txt","w");
    int j=0;
    for(j=0;j<n_h;j++)
    {
        fprintf(file,"%s",history[j]);
    }
    fclose(file);
}