#include "header.h";

void pinfo(char *inst)
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
    char *st=malloc(50*sizeof(char)), *exe=malloc(sizeof(char));

    sprintf(st,"/proc/%d/status",pid);
    sprintf(exe,"/proc/%d/exe",pid);

    FILE *f;

    if((f=fopen(st,"r"))==NULL)
    {
        perror("Process ID doesn't exist");
        return;
    }
    int n=3, i=0,m=18;
    char *mem=malloc(10000*sizeof(char)), *status = malloc(10000*sizeof(char)); 
    char str[1000];
    char* ex_path = malloc(10000*sizeof(char));
    while(fgets(str,1000,f))
    {
        i++;
        if(i==n)
        {
            strcpy(status,str);
        }
        if(i==m)
        {
            strcpy(mem,str);
        }
    }
    fclose(f);
    int path = readlink(exe,ex_path,2000);
    mem[0] = 'M';mem[1]='e';mem[2]='m';mem[3]='o';mem[4]='r';mem[5]='y';
    if(path==-1)
    {
        strcpy(ex_path,"Executable path not found");
    }
    else
    {
        ex_path[path] = '\0';
        ex_path = trim_dir(ex_path);
    }
    printf("Procces ID : %d\nProcess %s%sExecutable Path: %s\n",pid,status,mem,ex_path);
    return;

}