#include "header.h"

void quit()
{
    int i=0;
    for(i=0;i<curr_proc;i++)
    {
        kill(process_id[i], SIGKILL);
    }
    exit(0);
}