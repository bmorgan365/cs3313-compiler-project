%option noyywrap
%{
#include "p.h"
#include "p.tab.h"
%}

%%

"+"|
"-"|
"="|
";"|
"("|
")"|
":"|
"*"|
"/"|
"." {return yytext[0];}

"program" {return PROGRAM;}
"var" {return VAR;}
"integer" {return TYPE;}
"float" {return TYPE;}
"begin" {return BGN;}
"end" {return END;}
"print" {return PRINT;}

[a-zA-Z][a-zA-Z0-9]* {yyval.id = lookup(yyext); return ID;}

[0-9]+ {yyval.n = atol(yytext); return INT;}
[0-9]*"."[0-9]+ {yyval.z = atof(yytext); return FLOAT;}

[ \t\r\n] 

%%
