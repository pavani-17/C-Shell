#include "header.h"
  
 
void run_shell()
{
    prompt();
    get_input();
}

int main() 
{   
    printf("\n\n%s\t\t\t\t***************** Welcome to C Shell ******************%s\n\n",BLUE,NORMAL);
    get_val();
    while(1)
    {
        run_shell();
    }
    return 0; 
} 


    