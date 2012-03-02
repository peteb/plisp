#include <stdio.h>

#include "object.h"
#include "symbol.h"

int main(int argc, char *argv[]) {
  object_t *obj = obj_create();
  obj_add_slot(obj, "katt", sym_create("ahaha"));
  obj_print(obj);
  return 0;
}
