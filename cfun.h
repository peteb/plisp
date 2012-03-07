#ifndef PLISP_CFUN_H
#define PLISP_CFUN_H

#include "object.h"
#include <inttypes.h>

typedef object_t *(*cfun_ptr_t)(object_t *, object_t *);

typedef struct cfun {
  object_t header;
  cfun_ptr_t fun;
  uint64_t lazy_forms;
} cfun_t;

object_t *
cfun_create(cfun_ptr_t fun, uint64_t lazy_forms);

object_t *
cfun_apply(object_t *obj, object_t *env, object_t *args);

uint64_t
cfun_get_lazy_forms(object_t *obj);

#endif // !PLISP_CFUN_H
