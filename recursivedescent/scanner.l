/****
* Lex scanner for recursive descent statement example
* - note that the lex tool only recognizes old-C comments
*   in its own section, but we can use // in the C sections
****/

%{
// Header code to place in scanner

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// token type defs in scanner.h 
#include "scanner.h"
yystype yylval; 

// use this to print out the token names
char* tokenNames[] = {"none", "NUMBER", "IDENTIFIER", "EQUALS", "PLUS", "MINUS", "SEMICOLON"};

// debug flag only for scanner 
static int debug = 0;

// End header code
%}

/* This option is useful for printing out a syntax error */
/* message and printing out the line # it occurred on */
%option yylineno

/****** Token Patterns (regular expressions) ******/
%%
[ \t\n\r]+ { /* skip white space and do not return a token */ }
\=       {
            if (debug) printf("lex: equals symbol\n");
            yylval.ival = yytext[0];
            return(EQUALS);
         }
\+       {
            if (debug) printf("lex: plus symbol\n");
            yylval.ival = yytext[0];
            return(PLUS);
         }
\-       {
            if (debug) printf("lex: minus symbol\n");
            yylval.ival = yytext[0];
            return(MINUS);
         }
\;       {
            if (debug) printf("lex: semicolon symbol\n");
            yylval.ival = yytext[0];
            return(SEMICOLON);
         }
[0-9]+   {
            if (debug) printf("lex: number (%s)\n", yytext);
            yylval.ival = strtol(yytext,0,10);
            return(NUMBER);
         }
[a-zA-z]+ {
            if (debug) printf("lex: identifier (%s)\n", yytext);
            yylval.str = strdup(yytext);
            return(ID);
         }
.        {
            // this rule matches any single char not matched above
            fprintf(stderr, "lex: unknown char (%c)\n", yytext[0]);
         }

%%

//
// C functions to include in scanner
//

// yywrap() is called at end of input, to allow another
// input file to be opened, and input to continue; we don't
// use that capability.
int yywrap()
{
   //exit(0); // hard exit (not used anymore)
   return 1; // allow final token of 0 to be returned
}

#ifdef SCANNER_ONLY

// A main for standalone lex (uses just stdin as input)
int main(int argc, char **argv) 
{
   int token;
   do {
      token = yylex();
      if (token == 0) // indicates end of input
         break;
      printf("main: token = %s (%d)\n", tokenNames[token], token);
      if (token != ID) 
         printf("  integer attribute: %d\n", yylval.ival);
      else
         printf("  string attribute: %s\n", yylval.str);
   } while (1);
   // while (!feof(stdin)) doesn't work if redirecting a file
   // in because the file is read in and buffered, and eof is
   // true too early, causing lex to stop; rather, use while(1)
   // and then do a hard exit in yywrap(); ugly, but works!
   return 0;
}

#endif

