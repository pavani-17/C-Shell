#include "header.h"

void print_cur_dir() // Print the current working directory
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
        exit(0);
    }
    printf("%s\n",cwd);
}