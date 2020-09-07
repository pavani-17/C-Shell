#include "header.h"

void execute_inst(char** instruction, int len)
{
    char** n_ins;
    int i;
    for(i=0;i<len;i++)
    {
        remove_spaces(instruction[i]);
    }
    if(len>0 && strcmp(instruction[len-1],"&")==0)
    {
        if(strcmp(instruction[len-1],"&")==0)
        {
            background(instruction,len-1);
        }
    } 
    else if(strcmp(instruction[0],"pwd")==0)
    {
        print_cur_dir();
    }
    else if(strcmp(instruction[0],"cd")==0)
    {
        change_dir(instruction[1]);
        if(strlen(instruction[len-1])==0)
        {
            len--;
        }
        if(len>2)
        {
            printf("Too many arguments\n");
            return;
        }
    }
    else if(strcmp(instruction[0],"echo")==0)
    {
        echo_ex(instruction,len);
    }
    else if (strcmp(instruction[0],"ls")==0)
    {
        
       list_con(instruction,len);
    }
    else if(strcmp(instruction[0],"quit")==0)
    {
        fclose(file);
        int i=0;
        for(i=0;i<curr_proc;i++)
        {
            kill(process_id[i], SIGKILL);
        }
        exit(0);
    }
    else if(strcmp(instruction[0],"pinfo")==0)
    {
        if(len>2)
        {
            printf("Too many arguments\n");
            return;
        }
        pinfo(len==1 ? NULL : instruction[1]);
    }
    else if(strcmp(instruction[0],"history")==0)
    {
        history_dis(len > 1 ? instruction[1] : NULL);
    }
    else if(strcmp(instruction[0],"nightswatch")==0)
    {
        if(strlen(instruction[len-1])==0)
        {
            len--;
        }
        if(len!=4)
        {
            printf("Incorrect format for nightswatch.\n");
            return;
        }
        if(strcmp(instruction[1],"-n")!=0)
        {
            printf("Incorrect format for nightswatch.\n");
            return;
        }
        if(strcmp(instruction[3],"interrupts")==0)
        {
            watch_interrupt(instruction[2]);
        }
        else if(strcmp(instruction[3],"newborn")==0)
        {
            watch_process(instruction[2]);
        }
        else
        {
            printf("Please give a valid format for nightswatch\n");
        }        
    }
    else
    {
        if(strlen(instruction[len-1])==0)
        {
            len--;
        }
        foreground(instruction,len);
    } 
    
}

void remove_spaces(char* ins)
{
    int j=0,i;
    int len = strlen(ins);
    for(i=0;i<len;i++)
    {
        if(ins[i]==' ' || ins[i]=='\t' || ins[i]=='\n')
        {
            continue;
        }
        ins[j] = ins[i];
        j++;
    }
    ins[j] = '\0';
}
