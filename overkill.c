#include "header.h"

void overkill()  // Kills all background processes
{
    int i=0;
    for(i=0;i<curr_proc;i++)
    {
        if(kill(process_id[i], 9)<0)
        {
            perror("overkill");
            status = 0;
            return;
        }
    }
    status = 1;
}