%{
#include "y.tab.h"

void yyerror (char *s);
int yylex();
%}

digit [0-9]
id [a-zA-Z]+

%%

[ \t\n] 

"(" {return OP_OP;}
")" {return OP_CP;}
"def" {return KW_DEF;}
"exit" {return KW_EXIT;}
"+" {return OP_PLUS;}
"-" {return OP_MINUS;}
"/" {return OP_DIV;}
"*" {return OP_MULT;}

{digit}+"f"{digit}+ {

    char *delimeter = "f";
    char* numarator = strtok(yytext,delimeter);
    char* denumarator = strtok(NULL,delimeter);

    int num =  atoi(numarator);
    int denum = atoi(denumarator);


    
    yylval.frac.top = num;
    yylval.frac.bottom = denum;

    return VALUEF;
}

{id} { yylval.id = strdup(yytext); 
return IDENTIFIER;}


%%
int yywrap (void) {return 1;}

