%{
 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



// void yyerror(const char *s);
void yyerror(const char *s) {
    // fprintf(stderr, "Error: %s\n", s);
}
int yylex(void);




struct fraction calculateFraction(struct fraction first, struct fraction second, char operator);
struct fraction e_value(const char **str, const int var_values[52]);
struct fraction e_expr(const char **str, const int var_values[52]);
struct fraction e_frac(const char *expr, const int var_values[52]);

struct fraction calculator(struct fraction f1, struct fraction f2, char method);
struct fraction simplify(struct fraction f);


unsigned int gcd(unsigned int a, unsigned int b);

// struct fraction* frac_array = (struct fraction*)malloc(50 * sizeof(struct fraction));


typedef struct function{
    char name[50];
    char body[100];
    char params[3][50];

}function;

function frac_array[60];

int var_values[52] = {0}; 

int num_function = 0; 

%}


%union {
    char* id;
struct fraction {
    unsigned int top;
    unsigned int bottom;
} frac;
}

%token <id> IDENTIFIER
%token <frac> VALUEF
%token <id> KW_DEF KW_EXIT  OP_PLUS OP_MINUS OP_DIV OP_MULT OP_OP OP_CP 
%type <frac> exp
%type <id> body
%type <id> parametreler

%%

start: exp {printf("Result: %df%d\n",$1.top,$1.bottom);}
     |OP_OP KW_EXIT OP_CP {exit(0);}
     | start exp {printf("Result: %df%d\n",$2.top,$2.bottom);}
     | start OP_OP KW_EXIT OP_CP {exit(0);}
     | function {printf("function \n");}
     | start function {printf("function \n");}
     ;

exp: OP_OP OP_PLUS exp exp OP_CP {$$ = calculator($3, $4, '+');}
   | OP_OP OP_MINUS exp exp OP_CP {$$ = calculator($3, $4, '-');}
   | OP_OP OP_MULT exp exp OP_CP {$$ = calculator($3, $4, '*');}
   | OP_OP OP_DIV exp exp OP_CP {$$ = calculator($3, $4, '/');}


   | OP_OP IDENTIFIER exp OP_CP { 

        char* comp = $2;
        int index;
        for(int i=0; i < 60; i++){
            if (strcmp (frac_array[i].name, comp) == 0){
                index = i;
                break;
            }
        }
        var_values[(frac_array[index].params[0][0] - 'a') * 2] = $3.top;
        var_values[(frac_array[index].params[0][0] - 'a') * 2 + 1] = $3.bottom;
        // Set value of y (3/5)
        
        $$ = e_frac(frac_array[index].body, var_values);

        printf("%db%d\n", $$.top, $$.bottom);

   }
   | OP_OP IDENTIFIER exp exp OP_CP {
        char* comp = $2;
        int index;
        for(int i=0; i < 60; i++){
            if (strcmp (frac_array[i].name, comp) == 0){
                index = i;
                break;
            }
        }
        var_values[(frac_array[index].params[0][0] - 'a') * 2] = $3.top;
        var_values[(frac_array[index].params[0][0] - 'a') * 2 + 1] = $3.bottom;
        
        var_values[(frac_array[index].params[1][0] - 'a') * 2] = $4.top;
        var_values[(frac_array[index].params[1][0] - 'a') * 2 + 1] = $4.bottom;
        
        $$ = e_frac(frac_array[index].body, var_values);

        printf("%db%d\n", $$.top, $$.bottom);

   }
   
   
   | VALUEF {$$ = $1;}
   | IDENTIFIER {}
   ;

body:  OP_OP OP_PLUS IDENTIFIER IDENTIFIER OP_CP {

    char temp[50] = "";


    
    strcat(temp, "(");
    strcat(temp, " ");
    strcat(temp, "+");
    strcat(temp, " ");
    strcat(temp, $3);
    strcat(temp, " ");
    strcat(temp, $4);
    strcat(temp, " ");
    strcat(temp, ")");

    strcpy($$, temp);

    // printf("mal 7%s", $$);


    }
    |  OP_OP OP_MINUS IDENTIFIER  IDENTIFIER  OP_CP {
    
    char temp[50] = "";


    
    strcat(temp, "(");
    strcat(temp, " ");
    strcat(temp, "-");
    strcat(temp, " ");
    strcat(temp, $3);
    strcat(temp, " ");
    strcat(temp, $4);
    strcat(temp, " ");
    strcat(temp, ")");

    strcpy($$, temp);


    
    }
    |  OP_OP OP_MULT IDENTIFIER  IDENTIFIER  OP_CP {
        
    char temp[50] = "";


    
    strcat(temp, "(");
    strcat(temp, " ");
    strcat(temp, "*");
    strcat(temp, " ");
    strcat(temp, $3);
    strcat(temp, " ");
    strcat(temp, $4);
    strcat(temp, " ");
    strcat(temp, ")");

    strcpy($$, temp);


    
    }
    |  OP_OP OP_DIV IDENTIFIER  IDENTIFIER  OP_CP {
        
    char temp[50] = "";


    
    strcat(temp, "(");
    strcat(temp, " ");
    strcat(temp, "/");
    strcat(temp, " ");
    strcat(temp, $3);
    strcat(temp, " ");
    strcat(temp, $4);
    strcat(temp, " ");
    strcat(temp, ")");

    strcpy($$, temp);


    }
    |  VALUEF {sprintf($$, "%db%d", $1.top, $1.bottom);}
    |  IDENTIFIER { $$ = strdup($1);}
    ;

function:  OP_OP KW_DEF parametreler body  OP_CP { 
            
            strcpy(frac_array[num_function].body, $4);
            
            num_function++;
        }
        ;

parametreler: IDENTIFIER {
            strcpy(frac_array[num_function].name, $1);
            }
            | IDENTIFIER IDENTIFIER {
            strcpy(frac_array[num_function].name, $1);
            strcpy(frac_array[num_function].params[0], $2);
            
            }
            | IDENTIFIER IDENTIFIER IDENTIFIER {
            strcpy(frac_array[num_function].name, $1);
            strcpy(frac_array[num_function].params[0], $2);
            strcpy(frac_array[num_function].params[1], $3);
            }
            ;





%%

unsigned int gcd(unsigned int a, unsigned int b)
    {
        while (b != 0)
        {
            unsigned int t = b;
            b = a % b;
            a = t;
        }
    return a;
    }

    struct fraction simplify(struct fraction f)
    {
        unsigned int gcdValue = gcd(f.top, f.bottom);
        f.top /= gcdValue;
        f.bottom /= gcdValue;

        return f;
    }

    struct fraction calculator(struct fraction f1, struct fraction f2, char method)
    {
        struct fraction result;

        switch (method)
        {
            case '+':
                result.bottom = f1.bottom * f2.bottom;
                result.top = (f1.top * f2.bottom) + (f2.top * f1.bottom);
                break;
            case '-':
                result.bottom = f1.bottom * f2.bottom;
                result.top = (f1.top * f2.bottom) - (f2.top * f1.bottom);
                break;
            case '/':
                result.top = f1.top * f2.bottom;
                result.bottom = f1.bottom * f2.top;
                break;
            case '*':
                result.bottom = f1.bottom * f2.bottom;
                result.top = f1.top * f2.top;
                break;
            default:
                break;
        }

        return simplify(result);


    }

struct fraction calculateFraction(struct fraction first, struct fraction second, char operator) {
    struct fraction result;
    switch (operator) {
        case '+':
            result.top = first.top * second.bottom + second.top * first.bottom;
            result.bottom = first.bottom * second.bottom;
            break;
        case '-':
            result.top = first.top * second.bottom - second.top * first.bottom;
            result.bottom = first.bottom * second.bottom;
            break;
        case '*':
            result.top = first.top * second.top;
            result.bottom = first.bottom * second.bottom;
            break;
        case '/':
            result.top = first.top * second.bottom;
            result.bottom = first.bottom * second.top;
            break;
        default:
            result.top = 0;
            result.bottom = 1;
    }
    // printf("Calculate: %d/%d %c %d/%d = %d/%d\n", 
    //        first.top, first.bottom, operator, second.top, second.bottom, result.top, result.bottom);
    return result;
}

struct fraction e_value(const char **str, const int var_values[52]) {
    while (isspace(**str)) (*str)++; 

    if (isalpha(**str)) {
        int index = (tolower(**str) - 'a') * 2;
        struct fraction value = {var_values[index], var_values[index + 1]};
        (*str)++;
        return value;
    } else {
        struct fraction frac;
        frac.top = strtoul(*str, (char **)str, 10);
        if (**str == 'f') {
            (*str)++;
            frac.bottom = strtoul(*str, (char **)str, 10);
        } else {
            frac.bottom = 1; 
        }
        return frac;
    }
}

struct fraction e_expr(const char **str, const int var_values[52]) {
    while (isspace(**str)) (*str)++; 

    if (**str == '(') {
        (*str)++; 
        while (isspace(**str)) (*str)++;
        char operator = **str;
        (*str)++;


        struct fraction a = e_expr(str, var_values);
        struct fraction b = e_expr(str, var_values);

        while (isspace(**str)) (*str)++; 
        (*str)++;

        return calculateFraction(a, b, operator);
    } else {
        return e_value(str, var_values);
    }
}

struct fraction e_frac(const char *expr, const int var_values[52]) {
    return e_expr(&expr, var_values);
}



int main() {
    return yyparse();
}