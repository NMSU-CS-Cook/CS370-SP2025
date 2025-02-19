//
// Recursive descent parser skeleton, using 
// getchar() for single-character token input

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lookahead token, and token attributes from lex
int lookahead;

// Match: if lookahead matches the expected
// token argument, then "consume it" by 
// throwing it away and fetching the next token;
// otherwise print a syntax error message and exit
void match(int token)
{
   if (lookahead == token) {
       // "consume it" and get next token from scanner
       fprintf(stderr,"matched (%c)\n", token);
       lookahead = getchar();
   } else {
       fprintf(stderr, "Syntax error expected token %c, have %c\n",
               token, lookahead);
       exit(0); // every syntax error just does a hard exit
   }
}

//
// In here will go your recursive descent parser functions, 
// one for each nonterminal in the grammar
//



// driver main
int main(int argc, char **argv) 
{
   // get first token of input
   lookahead = getchar();
   // driver loop that just consumes tokens from scanner,
   // delete this for your actual parser
   do {
      match(lookahead); // will always match!
   } while (lookahead != EOF);
   // and start parsing by calling starting nonterminal function
   // startingNonterm()
   return 0;
}


