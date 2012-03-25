#include "gc.h"
#include "object.h"
#include <stdio.h>
#include <assert.h>

#define MAX_ROOTS 10

static object_t *roots[MAX_ROOTS] = {NULL};
static unsigned num_roots = 0;

void
gc_add_root(object_t *head) {
  assert(num_roots < MAX_ROOTS);
  roots[num_roots++] = head;
}

static void
gc_mark(object_t *obj) {
  printf("marking %p\n", obj);
  obj->type |= O_MARKED;

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

  while (node) {
	printf("[gc_collect] obj %p marked: %d\n", node, (node->type & O_MARKED ? 1 : 0));
	if (node->type & O_MARKED) {
	  node->type &= ~O_MARKED;
	}
	/* TODO: free here */
	
	node = node->prev;
  }
}

