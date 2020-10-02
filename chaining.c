#include "header.h"

void chaining(char *str)
{
    // Basic Idea
    // Execute the first command normally
    // From second, tie the input of the previous command to the logical operator
    // Left is always done, right may or may not be depending on short circuiting
    // n commands => n-1 
    // As one is done, every time both command and operator incremented
    char* str1 = malloc(100005*sizeof(char));
    strcpy(str1,str);
    char **ins = malloc(1000*sizeof(char*));
    char *tok;
    int symbol[10000];
    tok = strsep(&str,"@$");
    int i=0;
    while(tok!=NULL)
    {
        ins[i] = malloc(100000*sizeof(char));
        strcpy(ins[i],tok);
        tok = strsep(&str,"@$");
        i++;
    }
    long long int len = strlen(str1),j,k=0;
    for(j=0;j<len;j++)
    {
        if(str1[j]=='@')
        {
            symbol[k] = 1;
            k++;
        }
        else if(str1[j]=='$')
        {
            symbol[k]=0;
            k++;
        }
    }
    int p=0,q=0;
    int final_status;
    processPipe(ins[0]);
    final_status =status;
    for(p=1;p<i;p++,q++)
    {
        if(final_status==0 && symbol[q]==1)
        {
            continue;
        }
        else if (final_status && symbol[q]==0)
        {
            continue;
        }
        else
        {
            processPipe(ins[p]);
            if(symbol[q]==0)
            {
                final_status = final_status | status;
            }
            else
            {
                final_status = final_status & status;
            }   
        }
    }

    status = final_status;
}