#include "list.h"

object_t *
lst_cons(object_t *o1, object_t *o2) {
  object_t *lst = obj_create();
  obj_add_slot(lst, "first", o1);
  obj_add_slot(lst, "second", o2);
  return lst;
}

object_t *
lst_cons_lazy(object_t *o1, object_t *o2) {
  object_t *lst = obj_create();
  lst->type |= O_LAZY;
  obj_add_slot(lst, "first", o1);
  obj_add_slot(lst, "second", o2);
  return lst;
}

object_t *
lst_first(object_t *tup) {
  return obj_get_slot(tup, "first");
}

object_t *
lst_second(object_t *tup) {
  return obj_get_slot(tup, "second");
}


