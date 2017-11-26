# Specify Compiler
CC=gcc

#Specify options for compiler
CFLAGS=-c -Wall

program: project3.o MethodHeaders.h MLFQ.o FIFO.o  ShortestJobFirst.o RoundRobin.o MiscFunctions.o ProcessStruc.h
		$(CC) project3.c MethodHeaders.h MLFQ.c FIFO.c  ShortestJobFirst.c RoundRobin.c MiscFunctions.c ProcessStruc.h -lm -o program

project3: project3.c
		$(CC) $(CFLAGS) project3.c

MethodHeaders: MethodHeaders.h
		$(CC) $(CFLAGS) MethodHeaders.h

MLFQ: MLFQ.c
		$(CC) $(CFLAGS) MLFQ.c

FIFO: FIFO.c
		$(CC) $(CFLAGS) FIFO.c

ShortestJobFirst: ShortestJobFirst.c
		$(CC) $(CFLAGS) ShortestJobFirst.c

RoundRobin: RoundRobin.c
		$(CC) $(CFLAGS) RoundRobin.c

MiscFunctions: MiscFunctions.c
		$(CC) $(CFLAGS) MiscFunctions.c

ProcessStruc: ProcessStruc.h
		$(CC) $(CFLAGS) ProcessStruc.h

clean: 
		rm -rf *o program 