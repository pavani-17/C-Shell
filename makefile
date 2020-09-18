all:
	gcc input.c basic.c pwd.c cd.c execute_inst.c ls.c main.c echo.c pinfo.c foreground.c history.c background.c jobs.c kjob.c quit.c overkill.c fg.c nightwatch.c piping.c redirection.c -o shell
	clear 