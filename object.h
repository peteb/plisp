#ifndef PLISP_OBJECT_H
#define PLISP_OBJECT_H

typedef enum {
  O_BLOB,
  O_SYMBOL
} obj_type;

typedef struct slot {
  const char *id;
  struct object *value;
  struct slot *next;
} slot_t;

typedef struct object {
  obj_type type;
  struct slot *members;
} object_t;

object_t *obj_create();
void      obj_print(object_t *obj);
object_t *obj_add_slot(object_t *obj, const char *id, object_t *value);
object_t *obj_get_slot(object_t *obj, const char *id);

#endif // !PLISP_OBJECT_H
