#include "header.h"

void execute_inst(char** instruction, int len) // Execute the given instruction
{
    int i;
    for(i=0;i<len;i++)
    {
        remove_spaces(instruction[i]);
    }
    if(strlen(instruction[len-1])==0)
    {
        len--;
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
        quit();
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
    else if(strcmp(instruction[0],"setenv")==0)
    {
        if(len>3 || len<2)
        {
            printf("Incorrect number of arguments\n");
            return;
        }
        if(instruction[2]==NULL)
        {
            instruction[2]="";
        }
        if(setenv(instruction[1],instruction[2],1)<0)
        {
            perror("setenv ");
        }
        
    }
    else if(strcmp(instruction[0],"unsetenv")==0)
    {
        if(len!=2)
        {
            printf("Incorrect number of arguments\n");
            return;
        }
        if(unsetenv(instruction[1])<0)
        {
            perror("unsetenv ");
        }
    }
    else if(strcmp(instruction[0],"jobs")==0)
    {
        jobs();
    }
    else if(strcmp(instruction[0],"kjob")==0)
    {
        if(len!=3)
        {
            printf("Incorrect number of arguments\n");
            return;
        }
        kjob(instruction[1], instruction[2]);
    }
    else if(strcmp(instruction[0],"fg")==0)
    {
        if(len!=2)
        {
            fg(instruction[1]);
        }
    }
    else if(strcmp(instruction[0],"overkill")==0)
    {
        overkill();
    }
    else
    {
        foreground(instruction,len);
    } 
    
}

void remove_spaces(char* ins) // Removes the spaces in the input
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
