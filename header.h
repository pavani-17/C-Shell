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
#include <sys/wait.h>

#define max(a,b) (a>b ? a : b)

#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define NORMAL "\033[0m"
#define RED "\033[1;31m"
#define CYAN "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define red "\033[0;31m"

char *user_name, *system_name, *INTDIR, *PRDIR, *OPRDIR, *PREVDIR;


char *process[100005];
char curr_fore_proc[100005];
long long int process_id[100005] ;
int process_status[100005];
long long int curr_proc;
int curr_fore;
int status;

char ** history;
int n_h;
pid_t SHELL_PID;

/*Functions in basic.c */
void get_val();
void prompt();
char* inc_tilda(char * address);

/* Functions in execute_inst.c */
void execute_inst(char** instruction, int len);
void remove_spaces(char* ins);

/* Functions in input.c */
void get_input();
void process_input(char* input);
void execute_input(char* instructions);

/* Functions in cd.c */
char* trim_dir(char* cwd);
void change_dir(char* loc);
char* get_dir ();

/* Functions in pwd.c */
void print_cur_dir();

/* Functions in echo.c */
void echo_ex(char** inst, int len);

/* Functions in ls.c */

void list_con(char** loc, int len);
char check_flags_ls(char* inst);
void print_ls(char** loc, int hidden,int lf, int len, int files);
void flag_01 (char* loc, int hide);
void flag_23 (char* loc, int hide);

/* Functions in foreground.c */
void foreground(char **instruction, int len);

/* Functions in background.c */
void background(char **instruction, int len);

/* Functions in pinfo.c */
void pinfo(char *inst);

/* Functions in history.c */
void history_dis(char* ins);
void read_history();
void write_history();

/* Functions in nightwatch.c */
void watch_interrupt(char* t);
void watch_process(char* t);
void read_line (int n);
int input_available(int n);
void read_op();
void print_out(char* buffer);

/* Functions in piping.c */
void processPipe(char* input);

/* Functions in redirection.c */
void output_redirection(char* input);
void input_redirection(char* input);

/* Functions in jobs.c */
void jobs();

/* Functions in kjob.c */
void kjob(char* pid, char* sig_id);

/* Functions in fg.c */
void fg(char* pid);

/* Functions in quit.c */
void quit();

/* Functions in overkill.c */
void overkill();

/* Function in signal_handler.c */
void sigchld_handler(int signum);
void sigint_handler(int signum);
void sigtstp_handler(int signum);

/* Function in bg.c */
void bg(char* pid);

/* Functions in chaining.c */
void chaining(char *str);

// Later : Make seperate headers
// Make all errors to stderr so that can be displayed for piping and redirection too
// Replace pointer assignment