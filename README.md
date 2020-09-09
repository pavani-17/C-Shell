# CASH - A Shell in C

### CASH is a Linux BASH like shell written in C.

## How to Run?

1. Run `make` command to compile and link the shell files.
2. Run `./shell` to execute the shell.

## Features of the shell

1. `echo` <br>
    * Implemented in echo.c
    * Prints the given parameters after removing the extra spaces

2. `pwd` <br>
    * Implemented in current_dir.c
    * Prints the current working directory

3. `cd` [Location] <br>
    * Implemented in cd.c
    * Changes the current working directory to the mentioned directory. If no parameter is given, it changes the directory to the root directory of the shell.

4. `ls [-l -a -al -la] [Directory]` <br>
    * Implemented in ls.
    * Lists all the files and directories in the mentioned directory/directories. If no parameters are passed, lists the contents of current directory.

5. `pinfo [num]` <br>
    * Implemented in pinfo.c
    * Gives the informattion about `num` process. If `num` not mentioned, gives information about the current process.

6. `history [num]` <br>
    * Implemented in history.c
    * Gives the `num` number of previous commands run. If `num` is not mentioned, 5 is taken as the default value for `num`.

7. `nightswatch -n [num] [interrupts/newborn]` <br>
    * Implemented in nightswatch.c
    * If interrupts, gives the number of keyboard interrupts, else gives the newest process.
    * Gives the results at an interval of `num` seconds, till `q + Enter` is pressed.

8. Background process
    * Implemented in background.c
    * Input a command with `&` at the end to execute it as a background process.

9. `quit`
    * Quits the terminal.
    * Use this command to ensure proper closing (killing all persisting background processes) rather than  `Ctrl + C`
    
    