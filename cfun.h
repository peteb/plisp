#ifndef PLISP_CFUN_H
#define PLISP_CFUN_H

#include "object.h"

typedef object_t *(*cfun_ptr_t)(object_t *);

typedef struct cfun {
  object_t header;
  cfun_ptr_t fun;
} cfun_t;

object_t *cfun_create(cfun_ptr_t fun);
object_t *cfun_apply(object_t *obj, object_t *args);

#endif // !PLISP_CFUN_H
