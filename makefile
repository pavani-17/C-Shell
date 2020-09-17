all:
	gcc input.c basic.c current_dir.c cd.c execute_inst.c ls.c main.c echo.c pinfo.c foreground.c history.c background.c jobs.c kjob.c quit.c overkill.c fg.c nightwatch.c piping.c -o shell
	clear 