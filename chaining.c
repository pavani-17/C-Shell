#include "header.h"

void chaining(char *str)
{
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
    //printf("%d %d\n",i,k);
    int p=0,q=0;
    // for(p=0;p<k;p++)
    // {
    //     printf("%d\n",symbol[p]);
    // }
    int final_status;
    //printf("Executes %s\n",ins[0]);
    processPipe(ins[0]);
    final_status =status;
    for(p=1;p<i;p++,q++)
    {
        if(final_status==0 && symbol[q]==1)
        {
            //printf("Skips %s\n\n",ins[p]);
            continue;
        }
        else if (final_status && symbol[q]==0)
        {
            //printf("Skips %s\n\n",ins[p]);
            continue;
        }
        else
        {
            //printf("Executes %s\n",ins[p]);
            processPipe(ins[p]);
            // printf("\n");
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
    // for(p=0;p<i;p++)
    // {
    //     if(p!=0)
    //     {
    //         if(final_status==0 && symbol[q]==1)
    //         {
    //             prev_stat[p] = 0;
    //             p++;
    //             prev_stat[p] = 0;
    //             q++;
    //             continue;
    //         }
    //         if(final_status==1 && symbol[q]==0)
    //         {
    //             prev_stat[p] = 1;
    //             p++;
    //             prev_stat[p] = 1;
    //             q++;
    //             continue;
    //         }
    //     }
    //     processPipe(ins[p]);
    //     if(k==0)
    //     {
    //         return;
    //     }
    //     if(p==0)
    //     {
    //         final_status = status;
    //         prev_stat[p] = status;
    //     }
    //     prev_stat[p] = final_status;
    //     if(status==0 && symbol[q]==1)
    //     {
    //         p++;
    //         final_status = 0;
    //         prev_stat[p] = 0;
    //         q++;
    //     }
    //     else if(status==1 && symbol[q]==0)
    //     {
    //         p++;
    //         final_status = 1;
    //         prev_stat[p] = 1;
    //         q++;
    //     }
    //     else if(p==0)
    //     {
    //         final_status = status;
    //         prev_stat[p] = final_status;
    //     }
    //     else
    //     {
    //         if(symbol[q]==1)
    //         {
    //             final_status = status & prev_stat[p-1];
    //             prev_stat[p] = final_status;
    //             q++;
    //         }
    //         else
    //         {
    //             final_status = status | prev_stat[p-1];
    //             prev_stat[p] = final_status;
    //             q++;
    //         }
            
    //     }
        
    // }
    status = final_status;
}