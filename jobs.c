#include "header.h"

void jobs()
{
    int i;
    for(i=0;i<curr_proc;i++)
    {   
        if(process_status[i]==1)
        {
            continue;
        }
        else
        {
            char loc[100005];
            sprintf(loc,"/proc/%lld/stat",process_id[i]);
            FILE* f = fopen(loc,"r");
            if(f==NULL)
            {
                process_status[i] = 1;
                continue;
            }
            printf("[%d] ",i+1);
            char c;
            fscanf(f,"%*d %*s %c",&c);
            if(c=='T')
            {
                printf("Stopped ");
            }
            else
            {
                printf("Running ");
            }   
            fclose(f);
        }
        printf("%s [%lld]\n",process[i],process_id[i]);
    }
}