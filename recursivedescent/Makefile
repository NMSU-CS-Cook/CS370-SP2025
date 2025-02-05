#
# Make file for recursive descent statement example
# - executable is named "tdparser"
#

# flags and defs for built-in compiler rules
CFLAGS = -I. -Wall -Wno-unused-function
CC = gcc
LEX = lex

tdparser: parser.o lex.yy.o
	$(CC) -o tdparser parser.o lex.yy.o

# stand-alone scanner (do make clean first)
scanner: lex.yy.c
	$(CC) $(CFLAGS) -o scanner -DSCANNER_ONLY lex.yy.c

# lex "-d" flag turns on debugging output
lex.yy.c: scanner.l
	$(LEX) scanner.l

# clean the directory for a pure rebuild (do "make clean")
clean: 
	rm -f lex.yy.c a.out *.o scanner tdparser

