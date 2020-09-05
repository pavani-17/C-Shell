#include "header.h"

FILE* file;

void watch_interrupt(char* t)
{
    int n = atoi(t);

    if(n==0)
    {
        printf("Wrong format for nightswatch\n");
        return;
    }
    
    if(file==NULL)
    {
        printf("/procs/interrupts could not be opened");
        return;
    }
    while(1)
    {
        read_line(3);
        
        if(input_available(n))
        {
            char* prev = malloc(10*sizeof(char));
            int prev_size = 10;
            getline(&prev, &prev_size,stdin);
            if(prev[0]=='q')
            {
                break;
            }
            else
            {
                printf("To exit, press 'q'\n");
            }
        }        
    }

}

void watch_process(char* t)
{
    int n = atoi(t);
    if(n==0)
    {
        printf("Wrong format for nightswatch\n");
        return;
    }
    while(1)
    {
        read_op();
        if(input_available(n))
        {
            char* prev = malloc(10*sizeof(char));
            int prev_size = 10;
            getline(&prev, &prev_size,stdin);
            if(prev[0]=='q')
            {
                break;
            }
            else
            {
                printf("To exit, press 'q'\n");
            }
        }        
    }
}

int input_available(int n)
{
    struct timeval val;
    val.tv_usec=0;
    val.tv_sec=n;

    fd_set in;
    FD_ZERO(&in);
    FD_SET(STDIN_FILENO,&in);
    select(STDIN_FILENO+1,&in,NULL,NULL,&val);
    return (FD_ISSET(0,&in));
}

void read_line (int n)
{
    file = fopen("/proc/interrupts","r");
    int i = 0;
    char* buffer = malloc(100005*sizeof(char));
    int buffer_size = 100000;
    fseek(file,0,SEEK_SET);
    while(fgets(buffer,buffer_size,file))
    {
        i++;
        if(i==3)
        {
            break;
        }
    }
    print_out(buffer);
    fclose(file);
}

void print_out(char* buffer)
{
    char **tokens = malloc(100000*sizeof(char*));
    if(tokens==NULL)
    {
        printf("%s Error in assigning memory %s",RED,NORMAL);
        exit(0);
    }
    char* tok; 

    tok = strtok(buffer, " ");
    int i = 0;
    while(tok!=NULL)
    {
        tokens[i] = tok;
        tok = strtok(0," ");
        i++;
    }
    int p = get_nprocs();
    for(i=0;i<p;i++)
    {
        printf("  CPU%d\t",i);
    }
    printf("\n");
    for(int j=1;j<=p;j++)
    {
        printf("  %s\t",tokens[j]);
    }
    printf("\n\n");
}


void read_op()
{
    
    file = fopen("/proc/loadavg","r");
    
    if(file==NULL)
    {
        printf("/procs/interrupts could not be opened");
        return;
    }
    
    char* line = malloc(1005*sizeof(char));
    if(line==NULL)
    {
        printf("%s Error in assigning memory %s",RED,NORMAL);
        exit(0);
    }

    if(!fgets(line,1000,file))
    {
        printf("Error in reading");
        return;
    }
    char **tokens = malloc(100000*sizeof(char*));
    char* tok; 

    tok = strtok(line, " ");
    int i = 0;
    while(tok!=NULL)
    {
        tokens[i] = tok;
        tok = strtok(0," ");
        i++;
    }
    printf("Newest process: %s",tokens[4]);
    fclose(file);
}
