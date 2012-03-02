#include <stdio.h>

#include "object.h"

int main(int argc, char *argv[]) {
  object_t *obj = obj_create(O_BLOB);
  obj_print(obj);
  return 0;
}
