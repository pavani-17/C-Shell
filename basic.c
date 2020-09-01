#include "header.h"


void get_val()
{
    struct utsname uts;
    if(uname(&uts)<0)
    {
        perror("Uname() error");
        exit(1);
    }
    SYSTEM = malloc(1000000*sizeof(char));
    strcpy(SYSTEM,uts.nodename);

    struct passwd *pw;
    int uid;
    int c;

    uid = geteuid ();
    pw = getpwuid (uid);
    if(!pw)
    {
        fprintf (stderr,"%s: cannot find username for UID %u\n",
        _PROGRAM_NAME, (unsigned) uid);
        exit (1);
    }
    USER = pw->pw_name;

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
        return 1;
    }

    INTDIR = cwd;
    PRDIR = "~";
    OPRDIR = cwd;

}

void prompt()
{
    signal(SIGCHLD,sigchld_handler);
    printf("<%s%s@%s%s:%s%s%s> ",GREEN,USER,SYSTEM,NORMAL,BLUE,PRDIR,NORMAL);
}

char* inc_tilda(char * address)
{
    if(address[0]=='~')
    {
        char* new_addr;
        new_addr = malloc(100000*sizeof(char*));
        strcpy(new_addr,INTDIR);
        strcat(new_addr,address+1);
        return new_addr;        
    }
    else
    {
        return address;
    }
    
}

