#include "header.h"
  
 
void run_shell() // Execute the shell
{
    signal(SIGCHLD,sigchld_handler);
    prompt();
    get_input();
}

int main() 
{   
    printf("\n\n%s\t\t\t\t***************** Welcome to C Shell ******************%s\n\n",BLUE,NORMAL);
    get_val();
    FILE* file;
    file = fopen(".history.txt","r");
    if(file==NULL)
    {
        file = fopen(".history.txt","w");
        if(file==NULL)
        {
            printf("%sError opening history.txt%s",RED,NORMAL);
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
        printf("%s Error in assigning memory%s",RED,NORMAL);
        exit(0);
    }
    read_history();
    
    while(1)
    {
        run_shell();
    }
    return 0; 
} 


    