#include "header.h"

void overkill()
{
    int i=0;
    for(i=0;i<curr_proc;i++)
    {
        kill(process_id[i], SIGKILL);
    }
    curr_proc=0;
}