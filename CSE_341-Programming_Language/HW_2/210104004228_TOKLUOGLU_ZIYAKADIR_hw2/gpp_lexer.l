%{
#include <stdio.h>
#include <stdlib.h>
%}

digit [0-9]


id [a-zA-Z][a-zA-Z0-9]*


%%

[ \t\n] 

and {printf("KW_AND\n");}
or {printf("KW_OR\n");}
not {printf("KW_NOT\n");}
equal {printf("KW_EQUAL\n");}
less {printf("KW_LESS\n");}
nil {printf("KW_NIL\n");}
list {printf("KW_LIST\n");}
append {printf("KW_APPEND\n");}
concat {printf("KW_CONCAT\n");}
set {printf("KW_SET\n");}
def {printf("KW_DEF\n");}
for {printf("KW_FOR\n");}
if {printf("KW_IF\n");}
exit {printf("KW_EXIT\n");}
load {printf("KW_LOAD\n");}
display {printf("KW_DISPLAY\n");}
true {printf("KW_TRUE\n");}
false {printf("KW_FALSE\n");}

{digit}+"b"{digit}+ {
    printf("VALUEF\n");
}

{digit}+{id}+ {
    printf("SYNTAX_ERROR %s cannot be tokenized\n",yytext);
}


{id} {printf("IDENTIFIER\n");}

";;".* {printf("COMMENT\n");}




"+" printf("OP_PLUS\n");
"-" printf("OP_MINUS\n");
"/" printf("OP_DIV\n");
"*" printf("OP_MULT\n");
"(" printf("OP_OP\n");
")" printf("OP_CP\n");
";" printf("OP_COMMA\n");

. {
    printf("SYNTAX_ERROR %s cannot be tokenized\n",yytext);
    exit(1);
}

%%
int yywrap()
{
    return 1;
}



int main(int argc, char** argv){
    if(argc  >= 2 )
        yyin = fopen(argv[1], "r");
    else if(argc == 1)
        yyin = stdin;
    
    yylex();

    return 0;
}


 