%{
#include "object.h"
#include "symbol.h"
#include "list.h"
#include <stdio.h>
extern object_t *env;

%}

%union {
  const char *text;
  object_t *obj;
}

%token LPAREN
%token RPAREN
%token SYMBOL
%token QUOTE

%type <obj> expr
%type <obj> cons
%type <obj> q_cons

%%

line: expr                  {eval($1, env); }   
      | line expr           {eval($2, env); }
      ;

expr:  SYMBOL                       {$$ = sym_create(yylval.text, 0); }
       | QUOTE SYMBOL               {$$ = sym_create(yylval.text, 1); }
       | LPAREN cons RPAREN         {$$ = $2}
       | QUOTE LPAREN q_cons RPAREN {$$ = $3}
       ;

cons:  expr                 {$$ = lst_cons($1, NULL); }
       | expr cons          {$$ = lst_cons($1, $2); }
       ;

q_cons:  expr                 {$$ = lst_cons_lazy($1, NULL); }
         | expr q_cons        {$$ = lst_cons_lazy($1, $2); }
         ;

%%

int yyerror(const char *err) {
  printf("Error: %s\n", err);
  return 0;
}

        
