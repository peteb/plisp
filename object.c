#include "object.h"
#include "symbol.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

static const char *const 
obj_type_strtab[] = {
  "O_BLOB",
  "O_SYMBOL",
  "O_CFUN"
};

static object_t *
obj_lookup_slot(object_t *obj, const char *id);

static unsigned long alloc_count = 0;
static object_t *heap_head = NULL;

static void
obj_exit() {
  printf("obj terminate, %lu objects leaked\n", alloc_count);
}

void
obj_init() {
  atexit(obj_exit);
}

object_t *
obj_alloc(size_t sz, obj_type type) {
  gc_collect(heap_head);
  
  object_t *new_o = (object_t *)malloc(sz);
  assert(new_o && "failed to allocate memory for object");
  new_o->type = type;
  new_o->members = NULL;
  new_o->last_mark = 0;
  new_o->next = NULL;
  new_o->prev = heap_head;
  if (heap_head)
	heap_head->next = new_o;
  
  heap_head = new_o;
  alloc_count++;
  printf("[mem_alloc type: %x sz: %lu] %p\n", type, sz, new_o);
  
  return new_o;
}

void
obj_free(object_t *obj) {
  // TODO: free slots also
  // TODO: call destructor (ie; remove memory for symbol, etc)
  // TODO: unlink object
  printf("[mem_free at: %p]\n", obj);
  free(obj);
  alloc_count--;
}


object_t *
obj_create() {
  return obj_alloc(sizeof(object_t), O_BLOB);
}

object_t *
obj_add_slot(object_t *obj, const char *id, object_t *value) {
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

static object_t *
obj_lookup_slot(object_t *obj, const char *id) {
  slot_t *node = obj->members;
  while (node) {
    if (strcmp(node->id, id) == 0)
      return node->value;
	
    node = node->next;
  }

  return NULL;
}

static object_t *
obj_get_delegate(object_t *obj) {
  return obj_lookup_slot(obj, "delegate");
}

object_t *
obj_get_slot(object_t *obj, const char *id) {
  object_t *value;
  while (obj) {
    value = obj_lookup_slot(obj, id);
    if (value)
      break;

    obj = obj_get_delegate(obj);		
  }
  
  return value;
}


static void 
obj_print_rec(object_t *obj, int level) {
  char indent[256] = {0};
  int i;
  for (i = 0; i < level * 2 && i < sizeof indent; ++i)
    indent[i] = ' ';
  indent[i] = '\0';

  printf("%sobject %p, type %s %s (%x)\n", indent, obj,
         obj_type_strtab[OBJ_TYPE(obj)],
         (obj->type & O_LAZY ? "O_LAZY" : ""), obj->type);


  if (OBJ_TYPE(obj) == O_SYMBOL)
    printf("value: %s\n", sym_get_text(obj));
  
  slot_t *node = obj->members;
  while (node) {
    printf("%sslot '%s':\n", indent, node->id);
    if (node->value)
      obj_print_rec(node->value, level + 1);
    else
      printf("%s  (null)\n", indent);
	
    node = node->next;
  }
}

void 
obj_print(object_t *obj) {
  if (!obj) {
    printf("(null)\n");
    return;
  }
  
  obj_print_rec(obj, 0);
}

void 
obj_set_delegate(object_t *obj, object_t *deleg) {
  obj_add_slot(obj, "delegate", deleg);
}
