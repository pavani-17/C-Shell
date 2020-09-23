#include "header.h"

void print_cur_dir() // Print the current working directory
{
    char cwd1[100005];
    if (getcwd(cwd1, sizeof(cwd1)) == NULL)
    {
        perror("getcwd() error");
        status = 0;
        return;
    }
    printf("%s\n",cwd1);
}