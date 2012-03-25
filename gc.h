#ifndef PLISP_GC_H
#define PLISP_GC_H

#include "object.h"

void
gc_collect(object_t *head);

void
gc_add_root(object_t *head);

#endif // !PLISP_GC_H
