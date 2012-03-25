#include "symbol.h"
#include "object.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

object_t *
sym_create(const char *sym, int lazy) {
  symbol_t *new_sym = (symbol_t *)obj_alloc(sizeof(symbol_t), O_SYMBOL);
  new_sym->sym = strdup(sym);

  if (lazy)
    new_sym->header.type |= O_LAZY;
  
  return (object_t *)new_sym;
}

const char *
sym_get_text(object_t *obj) {
  assert(obj && OBJ_TYPE(obj) == O_SYMBOL && "target is not a symbol");
  return ((symbol_t *)obj)->sym;
}
