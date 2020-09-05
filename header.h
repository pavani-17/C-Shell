#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <limits.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <dirent.h> 
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/time.h>

#define _POSIX_SOURCE
#define _PROGRAM_NAME "whoami"

#define max(a,b) (a>b ? a : b)

#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define NORMAL "\033[0m"
#define RED "\033[0;31m"

char *USER, *SYSTEM, *INTDIR, *PRDIR, *OPRDIR;

char ** history;
int n_h;
FILE* file;

void get_val();
void prompt();
void get_input();
void process_input(char* input);
void execute_input(char** instructions, int mun_ins);
void execute_inst(char** instruction, int len);
void print_cur_dir();
void change_dir(char* loc);
void echo_ex(char** inst, int len);
void list_con(char** loc, int len);
char check_flags_ls(char* inst);
char* inc_tilda(char * address);
void print_ls(char** loc, int hidden,int lf, int len, int files);
void flag_01 (char* loc, int hide);
void flag_23 (char* loc, int hide);
void pinfo(char *inst);
char* trim_dir(char* cwd);
void background(char **instruction, int len);
void foreground(char **instruction, int len);
void sigchld_handler(int signum);
void history_dis(char* ins);
void read_history();
void write_history();
void watch_interrupt(char* t);
void watch_process(char* t);