#include <stdio.h>

#include "object.h"
#include "symbol.h"
#include "list.h"

int main(int argc, char *argv[]) {
  object_t *obj = obj_create();
  obj_add_slot(obj, "katt", sym_create("ahaha"));
  obj_print(obj);


  object_t *l1 = lst_cons(sym_create("print"), lst_cons(sym_create("hello"), NULL));
  
  return 0;
}
