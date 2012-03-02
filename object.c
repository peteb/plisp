#include "object.h"
#include <stdlib.h>
#include <stdio.h>

static const char *const obj_type_strtab[] = {
  "O_BLOB",
  "O_SYMBOL"
};

object_t *obj_create(obj_type tag) {
  object_t *new_obj = (object_t *)malloc(sizeof(object_t));
  new_obj->type = tag;
  new_obj->members = NULL;
  return new_obj;
}

static void obj_print_rec(object_t *obj, int level) {
  char indent[256] = {0};
  int i;
  for (i = 0; i < level * 2 && i < 255; ++i)
	indent[i] = ' ';
  indent[i] = '\0';

  printf("%sobject %p:\n", indent, obj);
  printf("%stype %s (%x)\n", indent, obj_type_strtab[obj->type], obj->type);

  slot_t *node = obj->members;
  while (node) {
	printf("%sslot '%s':\n", indent, node->id);
	obj_print_rec(node->value, level + 1);
	node = node->next;
  }
}

void obj_print(object_t *obj) {
  obj_print_rec(obj, 0);
/*   printf("-- %p ------------------\n", obj); */
/*   printf("type: %x\n", obj->type); */
  
}
