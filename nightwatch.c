#include "header.h"

// Files used
// interrupts => /proc/interrupts
// newborn => /proc/loadavg

void watch_interrupt(char* t) // Executes nightwatch interrupts
{
    int n = atoi(t);

    if(n==0)
    {
        fprintf(stderr,"Wrong format for nightswatch\n");
        status=0;
        return;
    }
    while(1)
    {
        read_line(3);
        
        if(input_available(n))
        {
            char* prev = malloc(10*sizeof(char));
            size_t prev_size = 10;
            getline(&prev, &prev_size,stdin);
            if(prev[0]=='q')
            {
                break;
            }
            else
            {
                fprintf(stderr,"To exit, press 'q'\n");
            }
        }        
    }

}

void watch_process(char* t) // Executes nightwatch newborn
{
    int n = atoi(t);
    if(n==0)
    {
        fprintf(stderr,"Wrong format for nightswatch\n");
        status = 0;
        return;
    }
    while(1)
    {
        read_op();
        if(input_available(n))
        {
            char* prev = malloc(10*sizeof(char));
            size_t prev_size = 10;
            getline(&prev, &prev_size,stdin);
            if(prev[0]=='q')
            {
                status=1;
                break;
            }
            else
            {
                printf("To exit, press 'q'\n");
            }
        }        
    }
}

int input_available(int n) // Checks if any letter(q for exiting) is available when nightwatch executes
{
    struct timeval val;
    val.tv_usec=0;
    val.tv_sec=n;

    fd_set in;
    FD_ZERO(&in); // Empty input file descriptor set
    FD_SET(STDIN_FILENO,&in); // Add STDIN to that set
    select(STDIN_FILENO+1,&in,NULL,NULL,&val);
    // Basic idea:
    // select function watches the given file decriptor sets (input,output, and error)
    // Checks if any of them is ready
    // Waits for val time => Time feature is exploited here rather than sleep(5)
    // Advantage => Gives immediate result (if sleep(5), checkes once in 5 sec)
    return (FD_ISSET(0,&in));
}

void read_line (int n) // Reads the required file
{
    FILE* file;   
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

void print_out(char* buffer) // prints the output for interrupts
{
    char **tokens = malloc(100000*sizeof(char*));
    if(tokens==NULL)
    {
        fprintf(stderr," Error in assigning memory ");
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
    int p = get_nprocs(); // Number of processors (Does not work in MacOS)
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


void read_op() // Reads the required file and prints the output for newborn
{
    FILE* file;
    file = fopen("/proc/loadavg","r");
    
    if(file==NULL)
    {
        printf("/procs/loadavg could not be opened\n");
        status=0;
        return;
    }
    
    char* line = malloc(1005*sizeof(char));
    if(line==NULL)
    {
        fprintf(stderr," Error in assigning memory\n");
        status=0;
        exit(0);
    }

    if(!fgets(line,1000,file))
    {
        printf("Error in reading\n");
        status = 0;
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
