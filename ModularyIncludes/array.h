// ****************************************************************************
//                                                                            *
//                                  ARRAY H                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// *****************************************************************************

#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdarg.h>

#include "modulaire.h"
#include "utils.h"

typedef struct    s_array
{
  t_module        module;
  unsigned int    len;
  void            **content;
  int             current;
}                 t_array;

typedef t_array * Array;

int               array_ctor(Array, va_list *);
int               array_dtor();

extern char       *__ARRAY;
extern t_module   __Array;

#endif /* __ARRAY_H__ */
