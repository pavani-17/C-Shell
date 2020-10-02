#include "header.h"

void quit()
{
    int i=0;
    for(i=0;i<curr_proc;i++)
    {
        kill(process_id[i], SIGKILL); // Kill all background process else vim & will give error
    }
    exit(0);
}