#include "header.h"
  
 
void run_shell()
{
    signal(SIGCHLD,sigchld_handler);
    prompt();
    get_input();
}

int main() 
{   
    printf("\n\n%s\t\t\t\t***************** Welcome to C Shell ******************%s\n\n",BLUE,NORMAL);
    get_val();
    file = fopen(".history.txt","r");
    if(file==NULL)
    {
        file = fopen(".history.txt","w");
        fclose(file);
    }
    history = malloc(21*sizeof(char*));
    read_history();
    fclose(file);
    while(1)
    {
        run_shell();
    }
    return 0; 
} 


    