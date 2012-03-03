%{
#include "object.h"
#include "plisp.tab.h"
%}

ws         [ \n\t]*
letter     [a-zA-Z]

%%

"("        {return LPAREN;}
")"        {return RPAREN;}
" "        {}
"'"        {return QUOTE;}
ws         {}
{letter}*  {yylval.text = strdup(yytext); return SYMBOL;}
.          {printf("Invalid str: '%s'\n", yytext);}
