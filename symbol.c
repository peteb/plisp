#include "symbol.h"
#include <stdlib.h>

object_t *sym_create(const char *sym) {
  symbol_t *new_sym = (symbol_t *)malloc(sizeof(symbol_t));
  new_sym->header.type = O_SYMBOL;
  new_sym->header.members = NULL;

  return (object_t *)new_sym;
}
