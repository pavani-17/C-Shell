#include "header.h"

char* trim_dir(char*cwd) // Put root dir into folder names
{
    int len = strlen(cwd), len1 = strlen(INTDIR);
    int i;
    for(i=0;i<len1;i++)
    {
        if(cwd[i]!=INTDIR[i])
        {
            break;
        }
    }
    if(len < len1)
    {
        i=0;
    }
    if(i==len1)
    {
        char* new = malloc(100000*sizeof(char));
        if(new==NULL)
        {
            printf("%s Error in assigning memory%s",RED,NORMAL);
            exit(0);
        }
        new[0] = '~';
        strcat(new,cwd+len1);
        return new;
    }
    else
    {
        return cwd;
    }
    
}

char* get_dir () // Get current directory
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
        exit(0);
    }
    if(strcmp(cwd,INTDIR)==0)
    {
        OPRDIR = INTDIR;
        return "~";
    }
    else
    {
        OPRDIR = cwd;
        return trim_dir(cwd);
    }
}

void change_dir(char* loc) // Change the directory
{
    if(loc==NULL || strlen(loc)==0)
    {
        loc="~";
    }
    else if(strcmp(loc,"-")==0)
    {
        strcpy(loc,PREVDIR);
    }
    //printf("%s\n",loc);
    strcpy(PREVDIR,PRDIR);
    loc = inc_tilda(loc);
    if(chdir(loc)!=0)
    {
        perror("cd failed");
        return;
    }
    PRDIR = get_dir();
    //printf("%s %s\n",PREVDIR,PRDIR);
}