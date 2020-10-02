#include "header.h"
  
 
void run_shell() // Execute the shell
{
    signal(SIGCHLD,sigchld_handler);  // Track background process
    signal(SIGINT,sigint_handler);    // Does nothing but sets status=0, do not ignore as child will inherit behavior
    signal(SIGTSTP,sigtstp_handler);  // Same as above **DONT IGNORE
    prompt();
    get_input();
}

int main() 
{   
    printf("\n\n%s\t\t\t\t    ***************** Welcome to C Shell ******************%s\n\n",BLUE,NORMAL);
    status=1;
    curr_fore = -1;
    get_val();
    SHELL_PID = getpid();
    FILE* file;
    file = fopen(".history.txt","r");
    if(file==NULL)
    {
        file = fopen(".history.txt","w");
        if(file==NULL)
        {
            printf("Error opening history.txt");
            exit(0);
        }
        fclose(file);
    }
    else
    {
       fclose(file);
    }
    
    history = malloc(21*sizeof(char*));
    if(history==NULL)
    {
        printf("Error in assigning memory");
        exit(0);
    }
    read_history();
    
    while(1)
    {
        run_shell();
    }
    return 0; 
} 