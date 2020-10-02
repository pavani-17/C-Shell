#include "header.h"

void output_redirection(char* input)
{
    int len = strlen(input);
    int flag = 0;
    if(input[len-1]=='&')
    {
        flag = 1;
        input[len-1] = '\0';
    }
    char* tok = strsep(&input,">");
    if(input==NULL)
    {
        if(flag)
        {
            char* tok1 = malloc((strlen(tok)+5)*sizeof(char));
            strcpy(tok1, tok);
            strcat(tok1, " &\0");
            input_redirection(tok1);
        }
        else
        {
            input_redirection(tok);
        }
        
        return;
    }
    int out_file=-1;
    int cout_temp = dup(1);
    if(input[0]=='>')
    {
        strsep(&input,">");
        remove_spaces(input);
        input = inc_tilda(input);
        out_file = open(input,O_WRONLY | O_APPEND | O_CREAT,0644);
        if(out_file<0)
        {
            perror("Redirection output file");
            return;
        }
    }
    else
    {
        remove_spaces(input);
        inc_tilda(input);
        out_file = open(input,O_WRONLY | O_CREAT | O_TRUNC,0644);
        if(out_file<0)
        {
            perror("Redirection output file");
            return;
        }   
    }
    dup2(out_file,1);
    if(flag==1)
    {
        char* tok1 = malloc((strlen(tok)+5)*sizeof(char));
        strcpy(tok1, tok);
        strcat(tok1, " &\0");
        input_redirection(tok1);
    }
    else
    { 
        input_redirection(tok);
    }

    dup2(cout_temp,1);
    close(out_file);
    return;
}

void input_redirection(char* input)
{
    int len = strlen(input);
    int flag = 0;
    if(input[len-1]=='&')
    {
        flag = 1;
        input[len-1] = '\0';
    }
    char* tok = strsep(&input, "<");
    if(input==NULL)
    {
        char* tok1 = malloc((strlen(tok)+5)*sizeof(char));
        strcpy(tok1, tok);
        if(flag==1)
        {
            strcat(tok1, " &\0");
            execute_input(tok1);
        }
        else
        {
            execute_input(tok1);
        }
        
        return;
    }
    int inp_file=0, cin_temp = dup(0);
    remove_spaces(input);
    input = inc_tilda(input);

    inp_file = open(input,O_RDONLY);
    if(inp_file<0)
    {
        perror("Redirection input file");
        return;
    }
    dup2(inp_file,0);
    char* tok1 = malloc((strlen(tok)+5)*sizeof(char));
    strcpy(tok1, tok);
    if(flag==1)
    {
        strcat(tok1, " &");
        execute_input(tok1);
    }
    else
    { 
        execute_input(tok1);
    }
    dup2(cin_temp,0);
    close(inp_file);
    return;
}



