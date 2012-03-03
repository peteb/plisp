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
	return cfun_apply(fun, args);
  }
  else {

  }
  
  return NULL;
}

object_t *eval(object_t *expr, object_t *env) {
  if (OBJ_TYPE(expr) == O_SYMBOL && !(expr->type & O_LAZY)) {
	return obj_get_slot(env, sym_get_text(expr));
  }
  else if (OBJ_TYPE(expr) == O_BLOB) {
	return apply(eval(sexp_fun(expr), env), eval_list(sexp_args(expr), env));
  }

  return expr;
}
