#include "object.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

static const char *const obj_type_strtab[] = {
  "O_BLOB",
  "O_SYMBOL"
};

static object_t *obj_lookup_slot(object_t *obj, const char *id);

object_t *obj_create() {
  object_t *new_obj = (object_t *)malloc(sizeof(object_t));
  new_obj->type = O_BLOB;
  new_obj->members = NULL;
  return new_obj;
}

object_t *obj_add_slot(object_t *obj, const char *id, object_t *value) {
  assert(!obj_lookup_slot(obj, id) && "slot already defined");
  
  slot_t *node = obj->members;
  if (!node) {
	/* we don't have any members at all */
	node = obj->members = (slot_t *)malloc(sizeof(slot_t));
  }
  else {
	slot_t *next = node;
	slot_t *last = NULL;
	while (next) {
	  last = next;
	  next = next->next;
	}

	node = last->next = (slot_t *)malloc(sizeof(slot_t));
  }
  
  node->id = strdup(id);
  node->value = value;
  
  return value;
}

static object_t *obj_lookup_slot(object_t *obj, const char *id) {
  slot_t *node = obj->members;
  while (node) {
	if (strcmp(node->id, id) == 0)
	  return node->value;
	
	node = node->next;
  }

  return NULL;
}

static object_t *obj_get_delegate(object_t *obj) {
  return obj_lookup_slot(obj, "delegate");
}

object_t *obj_get_slot(object_t *obj, const char *id) {
  object_t *value;
  while (obj) {
	value = obj_lookup_slot(obj, id);
	if (value)
	  break;

	obj = obj_get_delegate(obj);		
  }
  
  return value;
}


static void obj_print_rec(object_t *obj, int level) {
  char indent[256] = {0};
  int i;
  for (i = 0; i < level * 2 && i < 255; ++i)
	indent[i] = ' ';
  indent[i] = '\0';

  printf("%sobject %p, type %s (%x)\n", indent, obj, obj_type_strtab[obj->type], obj->type);

  slot_t *node = obj->members;
  while (node) {
	printf("%sslot '%s':\n", indent, node->id);
	obj_print_rec(node->value, level + 1);
	node = node->next;
  }
}

void obj_print(object_t *obj) {
  obj_print_rec(obj, 0);
}
