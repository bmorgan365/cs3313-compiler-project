%{
#include <stdio.h>
#include <stdlib.h>
#include "p.h"
%}

%union {
    struct id *id;
    enum node_type t;
    double z;
    long n;
    struct ast *ast;
    struct idlist *idlst;
    struct expr_list *exprlst;
}

%token<n> INT
%token<z> FLOAT
%token<t> TYPE
%token<id> ID
%token PROGRAM VAR BGN END PRINT

%type <ast> decl_list stmt_list devl stmt expr term factor
%type <idlist> id_list
%type <exprlst> expr_list

%%

program: PROGRAM ID ";" decl_list BGN stmt_list END "." ;
        eval($4); eval($6); freetree($6); freetree($4);}
        ;

decl_list:                      {$$ = NULL;}
        |decl decl_list ;       {if($2 == NULL) $$ = $1; else $$ = newlist($1, $2);}

decl: VAR id_list ":" TYPE ";" ;        {$$ = newdecl($2, $4);}

id_list: ID                     {$$ = newidlist($1, NULL);}
        | ID, id_list           {$$ = newidlist($1, $3);}
        ; 

stmt_list:                      {$$ = NULL;}
        | stmt stmt_list        {if($2 == NULL) $$ = $2; else $$ = newlist($1, $2);}
        ;

stmt: ID "=" expr ";"                   {$$ = newasgn($1, $3);}
        | PRINT "(" expr_list ")" ";"   {$$ = newprint($3);}
        ;

expr_list:                      {$$ = NULL;}
        | expr                  {$$ = newexprlist($1, NULL);}
        | expr "," expr_list    {$$ = newexprlist($1, $3);}
        ;

expr: term                      {$$ = $1;}
        | "+" term              {$$ = $2;}
        | "-" term              {struct ast *num = newint(0); $$ = newexpr(SUB, num, $2);}
        | expr "+" term         {$$ = newexpr(ADD, $1, $3);}
        | expr "-" term         {$$ = newexpr(SUB, $1, $3);}
        ;

term: factor                    {$$ = $1;}
        | term "*" factor       {$$ = newexpr(MUL, $1, $3);}
        | term "/" factor       {$$ = newexpr(DIV, $1, $3);}
        ;

factor: ID                      {$$ = newref($1);}
        | INT                   {$$ = newint($1);}
        | FLOAT                 {$$ = newfloat($1);}
        | "(" expr ")"          {$$ = $2;}
        ;

%%