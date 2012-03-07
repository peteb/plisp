#include "cfun.h"
#include <stdlib.h>
#include <assert.h>

object_t *
cfun_create(cfun_ptr_t fun, uint64_t lazy_forms) {
  cfun_t *new_cfun = (cfun_t *)malloc(sizeof(cfun_t));
  new_cfun->header.type = O_CFUN;
  new_cfun->header.members = NULL;
  new_cfun->fun = fun;
  new_cfun->lazy_forms = lazy_forms;
  
  return (object_t *)new_cfun;
}

object_t *
cfun_apply(object_t *obj, object_t *env, object_t *args) {
  assert(OBJ_TYPE(obj) == O_CFUN && "trying to apply non-cfun");
  return ((cfun_t *)obj)->fun(env, args);
}

uint64_t
cfun_get_lazy_forms(object_t *obj) {
  assert(OBJ_TYPE(obj) == O_CFUN &&
		 "trying to get lazy forms from non-cfun");
  return ((cfun_t *)obj)->lazy_forms;  
}
