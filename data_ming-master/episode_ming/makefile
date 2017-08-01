#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = gcc
CFLAGS  = -g -Wall #-DTEST_LIST

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: list1

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
list1:  list.o main.o util.o debug.o elem.o init.o file.o
	$(CC) $(CFLAGS) -o list1 list.o main.o util.o debug.o elem.o init.o file.o

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
list.o:  list.c head.h 
	$(CC) $(CFLAGS) -c list.c

# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
main.o:  main.c head.h 
	$(CC) $(CFLAGS) -c main.c

# To create the object file scanner.o, we need the source files
# scanner.c and scanner.h:
#
util.o:  util.c head.h 
	$(CC) $(CFLAGS) -c util.c

debug.o: debug.c
	$(CC) $(CFLAGS) -c debug.c
	
elem.o: elem.c
	$(CC) $(CFLAGS) -c elem.c

init.o: init.c
	$(CC) $(CFLAGS) -c init.c
file.o: file.c head.h
	$(CC) $(CFLAGS) -c file.c head.h
# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) list1 *.o *~

