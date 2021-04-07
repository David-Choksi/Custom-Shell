CFLAGS = -std=c99

myshell: myshell.c
	gcc $(CFLAGS) -o myshell myshell.c