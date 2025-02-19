//
// Recursive descent parser skeleton, using 
// getchar() for single-character token input
//
// Grammar to implement (S is starting nonterminal):
//
//  S -> A B '\n'
//  A -> a b A | empty
//  B -> b a C
//  C -> b a C | empty
//
// NOTE: the language of this grammar is exactly the
//       same as the language of the regular expression
//                 (ab)*(ba)+\n
//       (to test, enter one string on each input line, the
//        match function treats '\n' specially)
//
// NOTE2: remember that if a nonterminal can produce 
//        empty, then its default switch case does NOT
//        produce an error, it just falls out and returns
//        from the function as a successful rule completion
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int debug = 1;

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
       if (debug) fprintf(stderr,"matched (%c)\n", token);
       if (lookahead != '\n')
          lookahead = getchar();
          // don't wait when matching a \n, but then must
          // get the next token in main() after S() is matched
   } else {
       fprintf(stderr, "Syntax error expected token (%c), have (%c)\n",
               token, lookahead);
       exit(0); // our syntax error just does a program exit
   }
}

//
// In here will go your recursive descent parser functions, 
// one for each nonterminal in the grammar
// - if you encounter a syntax error (mismatch to the grammar),
//   print an error and exit, just like the match() function does
// - hint: nonterminals with only one production rule do not even
//         need a switch statement in their function

// prototypes
void S();
void A();
void B();
void C();

// driver main
int main(int argc, char **argv) 
{
   /**
   do {
      // get first token of input
      lookahead = getchar();
      // start parsing by calling starting nonterminal function
      S();
      printf("Successfully matched!\n");
   } while(1);
   return 0;
   **/
   
   // test driver loop that just consumes all tokens from scanner,
   // - delete or comment out this for your actual parser
   do {
      match(lookahead); // will always match itself!
   } while (lookahead != EOF);
   return 0;
}

