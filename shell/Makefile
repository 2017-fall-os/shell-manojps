# _*_Makefile_*_

CFLAG = -Wall -g
CC = gcc

shell: mytoc.o myshell.o
	cc -o shell myshell.o  mytoc.o
mytoc.o: mytoc.c
	cc -c mytoc.c
myshell.o: myshell.c mytoc.h
	cc -c myshell.c
clean:
	rm *.o shell
