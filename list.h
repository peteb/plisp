#ifndef PLISP_LIST_H
#define PLISP_LIST_H

#include "object.h"

object_t *
lst_cons(object_t *o1, object_t *o2);
object_t *
lst_cons_lazy(object_t *o1, object_t *o2);
object_t *
lst_first(object_t *tup);
object_t *
lst_second(object_t *tup);

#endif // !PLISP_LIST_H
