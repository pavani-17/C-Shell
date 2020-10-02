#include "header.h"

// Files used : /proc/pid/status    /proc/pid/exec

void pinfo(char *inst) // Executes pinfo command
{
    int pid;
    if(inst == NULL)
    {
        pid = getpid();
    }
    else
    {
        pid = atoi(inst);
    }
    char *st=malloc(50*sizeof(char)), *exe=malloc(50*sizeof(char));
    if(st==NULL)
    {
        fprintf(stderr,"%s Error in assigning memory %s",RED,NORMAL);
        status = 0;
        exit(0);
    }
    if(exe==NULL)
    {
        fprintf(stderr,"%s Error in assigning memory %s",RED,NORMAL);
        status = 0;
        exit(0);
    }

    sprintf(st,"/proc/%d/status",pid);
    sprintf(exe,"/proc/%d/exe",pid);

    FILE *f;

    if((f=fopen(st,"r"))==NULL)
    {
        printf("Process ID doesn't exist\n");
        status = 0;
        return;
    }
    int n=3, i=0,m=18;
    char *mem=malloc(10000*sizeof(char)), *status1 = malloc(10000*sizeof(char)); 
    if(mem==NULL)
    {
        printf("%s Error in assigning memory %s",RED,NORMAL);
        status = 0;
        exit(0);
    }
    char str[1000];
    char* ex_path = malloc(10000*sizeof(char));
    while(fgets(str,1000,f))
    {
        i++;
        if(i==n)
        {
            strcpy(status1,str);
        }
        if(i==m)
        {
            strcpy(mem,str);
        }
    }
    fclose(f);
    int path = readlink(exe,ex_path,2000);
    strtok(mem,":");
    mem = strtok(NULL,":");
    
    if(path==-1)
    {
        strcpy(ex_path,"Executable path not found");
    }
    else
    {
        ex_path[path] = '\0';
        ex_path = trim_dir(ex_path);
    }
    printf("Procces ID: %d\nProcess %sMemory: %sExecutable Path: %s\n",pid,status1,mem,ex_path);
    return;

}