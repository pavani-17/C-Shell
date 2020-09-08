#include "header.h"

void echo_ex(char** inst, int len) // Executes echo command
{
    int i;
    for(i=1;i<len;i++)
    {
        printf("%s ",inst[i]);
    }
    printf("\n");
    return;
}