#ifndef PLISP_EVAL_H
#define PLISP_EVAL_H

#include "object.h"

object_t *eval(object_t *expr, object_t *env);

#endif // !PLISP_EVAL_H
