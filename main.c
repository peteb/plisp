#include <stdio.h>

#include "object.h"
#include "symbol.h"
#include "list.h"
#include "eval.h"
#include "cfun.h"

object_t *
ENV_print(object_t *env, object_t *args) {
  if (!args) {
	printf("no args :(\n");
	return args;
  }
  
  /* print SYMBOL */
  if (OBJ_TYPE(lst_first(args)) == O_SYMBOL) {
	printf("%s\n", sym_get_text(lst_first(args)));
  }
  else {
	obj_print(lst_first(args));
  }
  return lst_first(args);
}

object_t *
ENV_define(object_t *env, object_t *args) {
  /* define NAME VALUE */
  
  object_t *name = lst_first(args);
  object_t *value = lst_first(lst_second(args));

  obj_add_slot(env, sym_get_text(name), value);
  
  return value;
}

object_t *
ENV_if(object_t *env, object_t *args) {
  /* if STATEMENT BODY ELSE */

  object_t *truth = lst_first(args);
  object_t *body = lst_first(lst_second(args)); /* TODO: optimize lst_seconds */
  object_t *els = lst_first(lst_second(lst_second(args)));

  if (!truth || OBJ_TYPE(truth) == O_SYMBOL && strcmp(sym_get_text(truth), "f") == 0) {
	/* NULL or 'f is false */
	return (els ? eval(els, env) : sym_create("void", 1));
  }

  /* everything else is true */
  return (body ? eval(body, env) : sym_create("void", 1));
}

object_t *
ENV_eval(object_t *env, object_t *args) {
  return eval(lst_first(args), env);  
}

object_t *env = NULL;

int
main(int argc, char *argv[]) {
  obj_init();


  env = obj_create();
  obj_add_slot(env, "print", cfun_create(ENV_print, 0x0));
  obj_add_slot(env, "define", cfun_create(ENV_define, 0x2));
  obj_add_slot(env, "if", cfun_create(ENV_if, 0x6));
  obj_add_slot(env, "eval", cfun_create(ENV_eval, 0x0));
  //  obj_add_slot(env, "my_name", lst_cons(env, lst_cons(lst_cons(sym_create("x", 1), NULL), lst_cons(sym_create("print", 0), lst_cons(sym_create("x", 0), NULL)))));

  yyparse();
  return 0;
  
/*   object_t *l1 = lst_cons(sym_create("my_name", 0), lst_cons(sym_create("hffello", 1), NULL)); */
/*   obj_print(l1); */


/*   object_t *env = obj_create(); */
  
/*   printf("eval\n"); */
/*   eval(l1, env); */
  
  return 0;
}
