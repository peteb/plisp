#include "eval.h"
#include "symbol.h"
#include "list.h"
#include "cfun.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

static object_t *
sexp_fun(object_t *expr) {
  return lst_first(expr);
}

static object_t *
sexp_args(object_t *expr) {
  return lst_second(expr);
}

static object_t *
eval_list(object_t *list, object_t *env, uint64_t lazy_forms) {
  if (!list) {
    return NULL;
  }

  object_t *new_node = obj_create();
  object_t *new_list = new_node;
  object_t *old_node = list;
  
  while (old_node) {
    object_t *old_val = lst_first(old_node);
    obj_add_slot(new_node, "first", (lazy_forms & 1 ? old_val : eval(old_val, env)));
    old_node = lst_second(old_node);
    new_node = obj_add_slot(new_node, "second",
                            (old_node ? obj_create() : NULL));
    lazy_forms >>= 1;
  }

  return new_list;
}

static object_t *
apply(object_t *fun, object_t *args, object_t *csenv) {
  assert(fun && "can't apply null fun"); 

  if (OBJ_TYPE(fun) == O_CFUN) {
    return cfun_apply(fun, csenv, args);
  }
  else if (OBJ_TYPE(fun) == O_BLOB) {
    // TODO: lam_get_definition  (for formals, env, body..)
    // TODO: lexical scoping, not dynamic...
    
    object_t *formals = lst_first(fun);
    object_t *body = lst_first(lst_second(fun));
    object_t *new_env = obj_create();
    obj_set_delegate(new_env, csenv);

    object_t *formal = formals;
    object_t *arg = args;
    uint64_t lazy_forms = 0;
    int pos = 0;
	
    while (arg && formal) {
      object_t *formal_def = lst_first(formal);
      obj_add_slot(new_env, sym_get_text(formal_def), lst_first(arg));

      formal = lst_second(formal);
      arg = lst_second(arg);
    }

    return eval(body, new_env);
  }
  else {
    assert(!"can't apply this");
  }
  
  return NULL;
}

object_t *
eval(object_t *expr, object_t *env) {
  if (expr->type & O_LAZY) {
    return expr;
  }
  
  if (OBJ_TYPE(expr) == O_SYMBOL) {
    object_t *slot = obj_get_slot(env, sym_get_text(expr));
    assert(slot && "couldn't look up symbol");
    object_t *val = slot;
    return val;
  }
  else if (OBJ_TYPE(expr) == O_BLOB) {
    uint64_t lazy_forms = 0;
    object_t *fun = eval(sexp_fun(expr), env);
    object_t *args = sexp_args(expr);
    
    if (args) {
      if (OBJ_TYPE(fun) != O_CFUN) {
        /* this expects the list to be formatted like a lambda */
        object_t *formal = lst_first(fun);
        int pos = 0;
        while (formal) {
          if (lst_first(formal)->type & O_LAZY) {
            assert(pos < 64 && "too late lazy formals");
            lazy_forms |= (1 << pos);
          }
          formal = lst_second(formal);
          pos++;
        }
      }
      else {
        lazy_forms = cfun_get_lazy_forms(fun);
      }
      
      args = eval_list(args, env, lazy_forms);
    }
    
    return apply(fun, args, env);
  }
  
  return NULL;
}
