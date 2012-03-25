#ifndef PLISP_OBJECT_H
#define PLISP_OBJECT_H

#include "string.h"

typedef enum {
  O_BLOB    = 0x00,
  O_SYMBOL  = 0x01,
  O_CFUN    = 0x02,
  O_LAZY    = 0x10
} obj_type;

typedef struct slot {
  const char *id;
  struct object *value;
  struct slot *next;
} slot_t;

typedef struct object {
  obj_type type;
  struct slot *members;
  struct object *prev, *next;
  unsigned last_mark;
} object_t;

#define OBJ_TYPE(obj) ((obj)->type & 0x0F)

/*
 * Static initialization for obj subsystem.
 */
void
obj_init();

/*
 * Allocates and sets the bare minimum of members for an object.
 */
object_t *
obj_alloc(size_t sz, obj_type type);

void
obj_free(object_t *);

/*
 * Constructor for obj type.
 */
object_t *
obj_create();

void
obj_print(object_t *obj);

object_t *
obj_add_slot(object_t *obj, const char *id, object_t *value);

object_t *
obj_get_slot(object_t *obj, const char *id);

void
obj_set_delegate(object_t *obj, object_t *deleg);

#endif // !PLISP_OBJECT_H
