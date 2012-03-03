#include <stdio.h>

#include "object.h"
#include "symbol.h"
#include "list.h"
#include "eval.h"
#include "cfun.h"

object_t *ENV_print(object_t *args) {
  printf("Print %s\n", sym_get_text(lst_first(args)));
  return args;
}

object_t *env = NULL;

int main(int argc, char *argv[]) {
  env = obj_create();
  obj_add_slot(env, "print", cfun_create(ENV_print));
  obj_add_slot(env, "my_name", lst_cons(env, lst_cons(lst_cons(sym_create("x", 1), NULL), lst_cons(sym_create("print", 0), lst_cons(sym_create("x", 0), NULL)))));
  
  yyparse();
  return 0;
  
/*   object_t *l1 = lst_cons(sym_create("my_name", 0), lst_cons(sym_create("hffello", 1), NULL)); */
/*   obj_print(l1); */


/*   object_t *env = obj_create(); */
  
/*   printf("eval\n"); */
/*   eval(l1, env); */
  
  return 0;
}
