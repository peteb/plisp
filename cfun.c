#include "cfun.h"
#include <stdlib.h>
#include <assert.h>

object_t *cfun_create(cfun_ptr_t fun) {
  cfun_t *new_cfun = (cfun_t *)malloc(sizeof(cfun_t));
  new_cfun->header.type = O_CFUN;
  new_cfun->header.members = NULL;
  new_cfun->fun = fun;

  return (object_t *)new_cfun;
}

object_t *cfun_apply(object_t *obj, object_t *args) {
  assert(OBJ_TYPE(obj) == O_CFUN && "trying to apply non-cfun");
  return ((cfun_t *)obj)->fun(args);
}
