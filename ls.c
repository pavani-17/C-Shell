#include "header.h"

void print_ls(char** loc, int hidden,int lf, int len, int files) // Call appropriate functions for printing
{
    
    if(files==0)
    {
        int flag = hidden + lf*2;

        switch(flag)
        {
            case 0:
                    flag_01(OPRDIR,0);
                    break;
            case 1:
                    flag_01(OPRDIR,1);
                    break;
            case 2:
                    flag_23(OPRDIR,0);
                    break;
            case 3:
                    flag_23(OPRDIR,1);
                    break;
        }
    }
       
    else
    {
        int i;
        for(i=1;i<len;i++)
        {
            int flag = hidden + lf*2;
            if(loc[i][0]!='-')
            {
                loc[i] = inc_tilda(loc[i]);
                switch(flag)
                {
                    case 0:
                            flag_01(loc[i],0);
                            break;
                    case 1:
                            flag_01(loc[i],1);
                            break;
                    case 2:
                            flag_23(loc[i],0);
                            break;
                    case 3:
                            flag_23(loc[i],1);
                            break;
                }
                if(i!=(len-1))
                {
                    printf("\n");
                }
            }
        }
    }
}
  
void list_con(char** loc,int len) // Check number of flags and directories
{ 
    int lf=0, hidden=0,i,files=0;

    for(i=1;i<len;i++)
    {
        if(loc[i][0]=='-')
        {
            char p = check_flags_ls(loc[i]);
            if(p=='l' || p=='c')
            {
                lf=1;
            }
            if(p=='a' || p=='c')
            {
                hidden=1;
            }
        }
        else
        {
            files++;
        }
        
    }

    print_ls(loc,hidden,lf,len,files);
} 

char check_flags_ls(char* inst) // Check flags of the command
{
    if(strcmp(inst,"-la")==0 || strcmp(inst,"-al")==0)
    {
        return 'c';
    }
    else if(strcmp(inst,"-a")==0)
    {
        return 'a';
    }
    else if(strcmp(inst,"-l")==0)
    {
        return 'l';
    }
    else
    {
        return 'z';
    }   
}

void flag_01 (char* loc, int hide) // For -a and no flags
{
    struct dirent *de;  
    DIR *dr = opendir(loc); 

    if (dr == NULL)  
    { 
        perror(loc); 
        status = 0;
        return;
    } 
    while ((de = readdir(dr)) != NULL)  
    {
        if(de->d_name[0] != '.' || hide)
        {
            printf("%s\n", de->d_name);
        } 
    }
    closedir(dr);      
}

void flag_23(char *loc, int hide) // For -l and -al
{
    struct dirent *de;  
    DIR *dr = opendir(loc); 
    struct stat mystat;

    if (dr == NULL)  
    { 
        fprintf(stderr,"%s Could not open directory: %s\n",red,loc ); 
        status = 0;
        return;
    }
    while((de=readdir(dr)) != NULL)
    {
        if((de->d_name)[0] != '.' || hide)
        {
            char buff[100000];
            sprintf(buff,"%s/%s",loc,de->d_name);
            stat(buff, &mystat);
            printf("%c%c%c%c%c%c%c%c%c%c",S_ISDIR(mystat.st_mode)?'d':'-',(mystat.st_mode & S_IRUSR)?'r':'-',(mystat.st_mode & S_IWUSR)?'w':'-',(mystat.st_mode & S_IXUSR)?'x':'-',(mystat.st_mode & S_IRGRP)?'r':'-',(mystat.st_mode & S_IWGRP)?'w':'-',(mystat.st_mode & S_IXGRP)?'x':'-',(mystat.st_mode & S_IROTH)?'r':'-',(mystat.st_mode & S_IWOTH)?'w':'-',(mystat.st_mode & S_IXOTH)?'x':'-');    
            struct passwd *pw = getpwuid(mystat.st_uid);
			struct group  *gr = getgrgid(mystat.st_gid);
			char date[100];
			strftime(date, 50, "%b  %d  %I: %M", gmtime(&(mystat.st_ctime)));
		    printf(" %5d %10s %10s  %10lld  %10s  %s\n", (int)mystat.st_nlink,pw->pw_name, gr->gr_name, (long long int)mystat.st_size, date, de->d_name);
        }
    }
    closedir(dr);
}