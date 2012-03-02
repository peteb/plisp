#ifndef PLISP_SYMBOL_H
#define PLISP_SYMBOL_H

#include "object.h"

typedef struct symbol {
  object_t header;
  const char *sym;
} symbol_t;

object_t   *sym_create(const char *sym);
const char *sym_get_text(object_t *obj);
  
#endif // !PLISP_SYMBOL_H
