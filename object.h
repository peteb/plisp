#ifndef PLISP_OBJECT_H
#define PLSIP_OBJECT_H

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

object_t *obj_create(obj_type tag);
void      obj_print(object_t *obj);

#endif // !PLISP_OBJECT_H
