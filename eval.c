#include "eval.h"
#include "symbol.h"
#include "list.h"
#include "cfun.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static object_t *sexp_fun(object_t *expr) {
  return lst_first(expr);
}

static object_t *sexp_args(object_t *expr) {
  return lst_second(expr);
}

static object_t *eval_list(object_t *list, object_t *env) {
  if (!list) {
    return NULL;
  }

  object_t *new_node = obj_create();
  object_t *new_list = new_node;
  object_t *old_node = list;
  
  while (old_node) {
    obj_add_slot(new_node, "first", eval(lst_first(old_node), env));
    old_node = lst_second(old_node);
    new_node = obj_add_slot(new_node, "second",
                            (old_node ? obj_create() : NULL));
  }

  return new_list;
}

static object_t *apply(object_t *fun, object_t *args) {
  assert(fun && "can't apply null fun"); 

  if (OBJ_TYPE(fun) == O_CFUN) {
    printf("FUN:\n");
    obj_print(fun);
    printf("ARGS:\n");
    obj_print(args);
    
    return cfun_apply(fun, args);
  }
  else {
    object_t *fun_env = lst_first(fun);
    object_t *formals = lst_first(lst_second(fun));
    object_t *body = lst_second(lst_second(fun));
    object_t *new_env = obj_create();
    obj_add_slot(new_env, "delegate", fun_env);

    object_t *formal = formals;
    object_t *arg = args;

    while (arg && formal) {
      obj_add_slot(new_env, sym_get_text(lst_first(formal)), lst_first(arg));
      formal = lst_second(formal);
      arg = lst_second(arg);
    }

    return eval(body, new_env);
  }
  
  return NULL;
}

object_t *eval(object_t *expr, object_t *env) {
  if (expr->type & O_LAZY) {
    return expr;
  }
  
  if (OBJ_TYPE(expr) == O_SYMBOL) {
    object_t *slot = obj_get_slot(env, sym_get_text(expr));
    assert(slot && "couldn't look up symbol");
    return slot;
  }
  else if (OBJ_TYPE(expr) == O_BLOB) {
    return apply(eval(sexp_fun(expr), env), eval_list(sexp_args(expr), env));
  }

  return NULL;
}
