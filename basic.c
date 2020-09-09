#include "header.h"


void get_val() // Get values of USER, SYSTEM and Root directory
{
    system_name = malloc(100005*sizeof(char));
    user_name = malloc(100005*sizeof(char));
    if(system_name==NULL)
    {
        printf("%s Error in assigning memory%s",RED,NORMAL);
        exit(0);
    }
    if(user_name==NULL)
    {
        printf("%s Error in assigning memory%s",RED,NORMAL);
        exit(0);
    }
    gethostname(system_name,100005);
    getlogin_r(user_name,100005);

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
        exit(0);
    }

    INTDIR = cwd;
    PRDIR = "~";
    OPRDIR = cwd;

}

void prompt() // Print the prompt everytime
{
    signal(SIGCHLD,sigchld_handler);
    printf("<%s%s@%s%s:%s%s%s> ",GREEN,user_name,system_name,NORMAL,BLUE,PRDIR,NORMAL);
}

char* inc_tilda(char * address)
{
    if(address[0]=='~')
    {
        char* new_addr;
        new_addr = malloc(100000*sizeof(char*));
        if(new_addr==NULL)
        {
            printf("%s Error in assigning memory%s",RED,NORMAL);
            exit(0);
        }
        strcpy(new_addr,INTDIR);
        strcat(new_addr,address+1);
        return new_addr;        
    }
    else
    {
        return address;
    }
    
}

