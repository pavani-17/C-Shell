#include "header.h"


void get_val() // Get values of USER, SYSTEM and Root directory
{
    // Might have to seperate to accomodate user change (Not sure)
    system_name = malloc(100005*sizeof(char));
    user_name = malloc(100005*sizeof(char));
    if(system_name==NULL)
    {
        fprintf(stderr,"%s Error in assigning memory%s",RED,NORMAL);
        exit(0);
    }
    if(user_name==NULL)
    {
        fprintf(stderr,"%s Error in assigning memory%s",RED,NORMAL);
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
    PREVDIR = malloc(100005*sizeof(char));
    PRDIR  = malloc(100005*sizeof(char));
    INTDIR = malloc(100005*sizeof(char));
    strcpy(INTDIR,cwd);
    strcpy(PRDIR,"~");
    OPRDIR = cwd;
    strcpy(PREVDIR,"~");
    // user_name = name of the user
    // system_name = hostname
    // INTDIR = Initial directory / Home directory of the shell
    // PREVDIR = Previous directory, initially ~, for cd -
    // PRDIR = Present directory in terms of ~
    // OPRDIR = Original present directory, absolute
}

void prompt() // Print the prompt everytime
{
    if(status==1)
    {
        printf("\n%s:')  %s",GREEN,NORMAL);
    }
    else
    {
        printf("\n%s:'(  %s",RED,NORMAL);
    }
    
    printf("%s%s@%s%s: %s%s%s $ ",CYAN,user_name,system_name,NORMAL,MAGENTA,PRDIR,NORMAL);
}

char* inc_tilda(char * address) // Adding ~ value to any loc (Changes absolute path to relative(~))
{
    if(address[0]=='~')
    {
        char* new_addr;
        new_addr = malloc(100000*sizeof(char*));
        if(new_addr==NULL)
        {
            fprintf(stderr,"%s Error in assigning memory%s",RED,NORMAL);
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

