//
// Recursive descent parser for simple statements
//   Copyright (C) 2025 Jonathan Cook
//
// A simpler grammar was started with, but then we
// removed left recursion and also did left factoring,
// so the implemented grammar is:
//  Stmts -> Stmt Stmts
//  Stmts -> _empty_
//  Stmt  -> id '=' Expr ';' 
//  Expr  -> Factor RestExpr
//  RestExpr -> '+' Expr
//  RestExpr -> '-' Expr
//  RestExpr -> _empty_
//  Factor  -> id
//  Factor  -> number
//
// NOTE: after class I added expression interpretation
// and variable assignment and lookup; HOWEVER, recursive
// descent parsing produces RIGHT associativity, and so 
// it does NOT evaluate expressions the way we are used to
// (LEFT associativity); e.g., subtraction applies to 
// everything to the right of it. An excellent but very
// detailed explanation of ways to solve this is at:
//   https://www.engr.mun.ca/~theo/Misc/exp_parsing.htm
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"

// Lookahead token, and token attributes from lex
int lookahead;
extern yystype yylval;
extern char* tokenNames[];

// debug flag only for parser
static int debug = 0;

// hash table and function for variable values; the 
// code does NOT check for collisions and so is UNSAFE 
// and only PROBABLY works most of the time
#define VSIZE 1003
int varValues[VSIZE];
int vhash(char* str) 
{
   int h = 0;
   for (int i=0; i < strlen(str); i++)
       h = str[i] + 3*h;
   return h % VSIZE;
}

// Nonterminal function prototypes
// - exprs and factors now return an int (for evaluation)
void stmts();
void stmt();
int expr();     // evaluates and returns an integer
int restExpr(); // evaluates and returns an integer
int factor();   // evaluates and returns an integer

// Match: if lookahead matches the expected
// token argument, then "consume it" by 
// throwing it away and fetching the next token;
// otherwise print a syntax error message and exit
void match(int token)
{
   if (lookahead == token) {
       // "consume it" and get next token from scanner
       lookahead = yylex();
   } else {
       fprintf(stderr, "Syntax error expected token %s, have %s\n",
               tokenNames[token], tokenNames[lookahead]);
       exit(0); // every syntax error just does a hard exit
   }
}

// Stmts nonterminal function 
void stmts()
{
   switch (lookahead) {
    case ID:
       stmt(); stmts(); // apply production rule RHS
       if (debug) printf("matched Stmts rule\n");
       break;
    default:
       // empty rule, not a syntax error
       break;
   }
}

// Stmt nonterminal function 
void stmt()
{
   char* varName;
   int val, i;
   switch (lookahead) {
    case ID:
       // save lexeme as varName before matching
       varName = (char*) malloc(strlen(yylval.str)+2);
       strcpy(varName, yylval.str);
       // apply production rule RHS: id '=' Expr ';'
       match(ID); match(EQUALS); val = expr(); match(SEMICOLON);
       if (debug) printf("matched Stmt rule:\n");
       i = vhash(varName); // look up variable in hash table
       varValues[i] = val; // do assignment
       printf("var %s is set to %d\n", varName, val);
       free(varName);
       break;
    default:
       fprintf(stderr, "Syntax error in stmt()!\n");
       exit(0);
       break;
   }
}

// Expr nonterminal function 
int expr()
{
   int v1, v2;
   switch (lookahead) {
    case ID:
    case NUMBER:
       //production rule RHS: Factor RestExpr
       v1 = factor(); v2 = restExpr();
       if (debug) printf("matched Expr rule (%d,%d)\n", v1, v2);
       return v1+v2; // subtract will negate its own value,
       break;        // so adding these is ok here
    default:
       fprintf(stderr, "Syntax error in expr()!\n");
       exit(0);
       break;
   }
   return 0;
}

// restExpr nonterminal function 
int restExpr()
{
   int val;
   switch (lookahead) {
    case PLUS:
       match(PLUS); val = expr();
       if (debug) printf("matched RestExpr plus rule\n");
       return val;
       break;
    case MINUS:
       match(MINUS); val = expr();
       if (debug) printf("matched RestExpr minus rule\n");
       return 0 - val; // make v negative, for minus
       break;
    default:
       // empty rule, not a syntax error
       break;
   }
   return 0;
}

// Factor nonterminal function 
int factor()
{
   char* varName;
   int val, i;
   switch (lookahead) {
    case ID:
       // save lexeme as varName before matching
       varName = (char*) malloc(strlen(yylval.str)+2);
       strcpy(varName, yylval.str);
       // now apply production rule and match ID
       match(ID);
       if (debug) printf("matched factor ID (%s)\n", varName);
       i = vhash(varName); // look up variable in hash table
       val = varValues[i];
       free(varName);
       return val;
       break;
    case NUMBER:
       // save integer value of lexeme before matching
       val = yylval.ival;
       // now apply production rule and match number
       match(NUMBER);
       if (debug) printf("matched factor NUMBER (%d)\n", val);
       return val;
       break;
    default:
       fprintf(stderr, "Syntax error in expr()!\n");
       exit(0);
       break;
   }
   return 0;
}

int main(int argc, char **argv) 
{
   // get first token of input
   lookahead = yylex();
   // and start parsing
   stmts();
   return 0;
}


