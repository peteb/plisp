#include "gc.h"
#include <stdio.h>
#include <assert.h>

#define MAX_ROOTS 10

static object_t *roots[MAX_ROOTS] = {NULL};
static unsigned num_roots = 0;
static unsigned current_collect = 1;

void
gc_add_root(object_t *head) {
  assert(num_roots < MAX_ROOTS);
  roots[num_roots++] = head;
}

static void
gc_mark(object_t *obj) {
  printf("marking %p\n", obj);
  obj->last_mark = current_collect;

  /* recurse slots */
  slot_t *slot = obj->members;
  while (slot) {
	gc_mark(slot->value);
	slot = slot->next;
  }
}

void
gc_collect(object_t *node) {
  /* first, recursively mark all the objects in the roots */
  int i;
  for (i = 0; i < num_roots; ++i) {
	gc_mark(roots[i]);
  }

  printf("[gc_collect] current collection %d\n", current_collect);
  
  while (node) {
	printf("[gc_collect] obj %p last_mark %d\n", node, node->last_mark);
	node = node->prev;
  }

  current_collect++;
}

