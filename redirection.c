#include "header.h"

void output_redirection(char* input)
{
    char* tok = strsep(&input,">");
    if(input==NULL)
    {
        input_redirection(tok);
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
    input_redirection(tok);
    dup2(cout_temp,1);
    close(out_file);
    return;
}

void input_redirection(char* input)
{

    char* tok = strsep(&input, "<");
    if(input==NULL)
    {
        execute_input(tok);
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
    execute_input(tok);
    dup2(cin_temp,0);
    close(inp_file);
    return;
}



