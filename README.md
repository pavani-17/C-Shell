# CASH - A Shell in C

### CASH is a Linux BASH like shell written in C. It implements all shell commands and supports pipelining, redirection and chaining.

## How to Run?

1. Run `make` command to compile and link the shell files.
2. Run `./shell` to execute the shell.

## Features of the shell

1. Many commands are inbuilt which are explained in the following section. All the other commands which are to be executed in foreground are implemented using `execvp`. So, all the commands available in Bash can be executed in Cash.

2. The prompt for taking the next command displays the `username`, `hostname` and the `present working directory`. The directory in which the shell is run is taken to be the home directory `~` of the shell. The present working directory is displayed either in terms of `~` (if `~` is its ancesstor) or as absolute path.

3. Cash provides process management by allowing to control between background and foreground processes and switch between them. The background process control is provided using `fg`, `bg` and `&`, which is explained in detail later.

4. Signals like `SIGSTP` (  <kbd>Ctrl</kbd> `+` <kbd>Z</kbd>  ) and `SIGINT`  (  <kbd>Ctrl</kbd> `+` <kbd>C</kbd>  ) are handled using appropriate signal handlers which is explained later.

5. Piping and Redirection are provided and handled as Bash handles them. However, as of now, background process is not supported by piping. Redirection supports background processes.

6. `EXIT CODE` (success or failure) of the previous command is displayed along the prompt for the next command. <kbd>:')</kbd>  denotes success and  <kbd>:'(</kbd> denotes failure.

7. The aforementioned `EXIT CODE` can be computed for multiple commands using chaining of commands using `AND` (  <kbd>@</kbd> ) and `OR`  ( <kbd>$</kbd> ), which calculate the resultant `EXIT CODE` by applying `AND` and `OR` operations on the commands.

8. The shell supports semi-colon  <kbd>;</kbd>  seperated commands. In this case, the `EXIT CODE` is determined by the last command in the sequence. 

## Inbuilt Commands

1. `echo` <br>
    * Implemented in `echo.c`
    * Takes a string argument and prints it after removing the extra spaces. Does not support `$env_var`.

2. `pwd` <br>
    * Implemented in `pwd.c`
    * Prints the current working directory.
    * Uses the `getcwd()` system call.

3. `cd [location]` <br>
    * Implemented in `cd.c`
    * Changes the current working directory to the mentioned directory. If no parameter is given, it changes the directory to the root directory of the shell.
    * If `~` is present in the given `location`, it is replaced with the home directory of the shell.
    * If `location` is `-`, it is interpreted as the previous working directory of the shell.
    * Implemented using `chdir()` system call.

4. `ls [-l -a -al -la] [Directory]` <br>
    * Implemented in `ls.c`
    * Lists all the files and directories in the mentioned directory/directories. If no parameters are passed, lists the contents of current directory.
    * `-l` flag lists the long format of `ls`, providing additional details such as permissions, owner, time of creation etc.
    * `-a` flag includes the hidden files/diectories in the listing.
    * The flags and directories can be provided in any order.
    * Uses the `readdir()` system call.

5. `pinfo [process_id]` <br>
    * Implemented in `pinfo.c`
    * Gives the information about `process_id` process. If `process_id` not mentioned, gives information about the current process.
    * The information includes Process ID, Process Name, State of the process and the exceutable path of the process.
    * Uses the files `/proc/process_id/status` and `/proc/process_id/exec` to fetch the required information. 

6. `history [num]` <br>
    * Implemented in `history.c`
    * Gives the `num` number of previous commands run. If `num` is not mentioned, 10 is taken as the default value for `num`.
    * Continous repetitions and blank lines are avoided in the history.

7. `nightswatch -n [seconds] [interrupts/newborn]` <br>
    * Implemented in `nightwatch.c`
    * If `interrupts`, gives the number of keyboard interrupts, else if `newborn` gives the newest process.
    * Gives the results at an interval of `seconds`,  till <kbd>q</kbd>  +  <kbd>Enter</kbd> is pressed.
    * For `interrupts`, the file `/proc/interrupts` is used.
    * For `newborn`, the file `/proc/loadavg` is used. 

8. `setenv [var] [val]` <br>
    * Implemented in `execute_inst.c`
    * Creates the environment variable `var` and assigns the value `val` to it.
    * If `val` is not provided, it is interpreted as `val = NULL`.
    * Uses the `setenv()` function.

9. `unsetenv [var]`
    * Implemeted in `execute_inst.c`
    * Deletes the environment variable named `val` along with its value.
    * Uses the `unsetenv()` function.

10. `jobs`
    * Implemented in `jobs.c`
    * Lists all the background process along with their `job_id`, `pid` and `status` (Running or Stopped).
    * Information required is taken from `/proc/pid/stat` file.

11. `kjob [job_id] [signal]`
    * Implemented in `kjob.c`
    * Sends `signal` to the process with Job ID `job_id`.
    * Uses the `kill()` system call.

12. `fg [job_id]`
    * Implemented in `fg.c`
    * Makes a stopped background process with Job ID `job_id` continue as a foreground process.

13. `bg [job_id]`
    * Implemented in `bg.c`
    * Continous a stopped background process in the background. 

14. `overkill`
    * Implemented in `overkill.c`
    * Terminates all background processes.
    * Uses the `kill()` system call with `SIGKILL`.


15. `quit`
    * Implemented in `quit.c`
    * Quits the terminal.
    * Use this command to ensure proper closing (killing all persisting background processes).
    * <kbd>Ctrl</kbd> + <kbd>D</kbd> provides the same functionality.

## Executional Details     

1. Any command ending with `&` is treated as a background process the shell does not wait for its execution. If such a process requests terminal control, it will automatically suspended in the background. The shell keeps track of all background processes and alerts the user on their completion.

2. <kbd>|</kbd> is used for piping of commands, i.e, Output of one command serves as input for the next. <br>
Example:
    ```
    username@hostname $ grep "new" temp.txt | sort | wc
    ```

3. <kbd><</kbd> is used for input redirection. <kbd>></kbd> (for overwriting) and <kbd>>></kbd> (for apending) are used for output redirection.<br>
Example:
    ```
    # Input Redirection
    username@hostname $ diff file1.txt file2.txt > output.txt 

    # Output Redirection
    username@hostname $ sort < lines.txt

    # Input and Output Redirection
    username@hostname $ sort < lines.txt >> sortedlines.txt
    ```

4. Commands are chained using logical `AND` and `OR` operators, such that the `EXIT CODE` of the entire chain is the logical `AND` or `OR` (respectively) of the individual exit codes. These operators short circuit, have equal precedence and are evaluated left-to-right.<br>
Example:
    ```
    :') username@hostname > ls $ echo penguins @ echo fail
     oswald     henry     pingu     
     fail

    :') username@hostname >  ps -Q $ ps -Q @ ps
      error: unsupported SysV option
      error: unsupported SysV option
      .....

    :'( username@hostname >
    ```

5. <kbd>Ctrl</kbd> + <kbd>C</kbd> sends the `SIGINT` signal and terminates any foreground process.

6. <kbd>Ctrl</kbd> + <kbd>Z</kbd> sends the `SIGSTP` signal and suspends any running foreground process.

7. <kbd>Ctrl</kbd> + <kbd>D</kbd> is an `EOF` character and terminates the shell.

8. The order of precedence (the order in which the command is broken down is as follows): <br>
    ``` 
    ; > @,$ (Logical) > Piping (|) > (<,>,>>) Redirection > Background(&)
    ```
## Implementational Details

* `piping.c` <br>
   Contains the implementation of piping using `pipe` system call and `dup` system call.

* `redirection.c` <br> 
    Contains the implementation of input redirection and output redirection in two functions. Uses the `dup` and `dup2` function calls.

* `chaining.c` <br>
    Contains the implementation of command chaining which binds looser than `;` but stronger than `|,>,<,>> and &`.

* `background.c` <br>
    Implementation of background processes indentified by `&`. Creates a new child process using `fork()` and the shell does not wait for its completion. 

* `basic.c` <br>
    Conatins some basic functions such as `get_val()` for getting the values of `username`, `hostname` and `home directory` of the shell, `prompt()` for displaying the prompt and `inc_tilda` for substituting the home directory in all the in-built commands which use `location`.

* `execute_inst.c` <br>
    All commands are processed and corresponding functions called using the function `execute_inst()`. Also contains a `remove_spaces()` for basic string manipulation and space removal.

* `input.c` <br>
    Takes input `get_input()`, processes it (tokenizes on the basis of `;`) `process_input` (Calls the chaining function) and executes the input after receiving individial instructions (`execute_input()`).

* `history.c` <br>
    Along with the implementation of history command, it also contains `write_history` and `read_history` which write the history to a file `.history.txt` and read from it respectively. This ensures that history is preserved across sessions.

* `main.c` <br>
    Contains the `main()`. The shell execution starts from here.

* `signal_handlers.c` <br>
    Contains the signal handlers for `SIGCHLD` (used to keep track of background processes), `SIGINT` and `SIGTSTP` signals.
    
* `header.h` <br>
    Contains all required headers and global variables

### To Do
1. Arrow keys for command-recall
2. <kbd>Tab</kbd> for auto completion
3. `&` for piped processes.
4. Environment variables support
5. Aliasing <br>
......
