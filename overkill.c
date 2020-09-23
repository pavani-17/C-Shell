#include "header.h"

void overkill()
{
    int i=0;
    for(i=0;i<curr_proc;i++)
    {
        if(kill(process_id[i], SIGKILL)<0)
        {
            status = 0;
            return;
        }
    }
    curr_proc=0;
    status = 1;
}