#include "header.h"

void print_cur_dir()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
        return 1;
    }
    printf("%s\n",cwd);
}