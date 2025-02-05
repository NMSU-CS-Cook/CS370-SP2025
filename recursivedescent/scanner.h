//
// In using lex by itself, we must have explicit 
// definitions for tokens and token attributes, so
// we put this in a header file to share with the 
// parser. When lex is used with yacc, yacc is 
// responsible for generating token definitions
//

#define NUMBER     1
#define ID         2
#define EQUALS     3
#define PLUS       4
#define MINUS      5
#define SEMICOLON  6

// token attribute defs: "ival" is the name
// for an integer attribute, "str" for a 
// string attribute; with using a union, these
// overlap in memory, so each token has only 
// one or the other
typedef union { int ival; char* str; } yystype;
// def below is needed for yacc, not for this example
#define YYSTYPE yystype

// scanner function prototype, for use in parser
extern int yylex(void);


