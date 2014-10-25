// ****************************************************************************
//                                                                            *
//                                 STRING H                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// *****************************************************************************

#ifndef __STRING_H__
#define __STRING_H__

#include <stdarg.h>

#include "modulaire.h"
#include "utils.h"

typedef struct         s_string
{
  t_module             module;
  unsigned int         len;
  void                 *content;
  fct                  set;
  pfct                 split;
  char                 (*at)();
  fct                  epur;
}                      t_string;

typedef t_string *     String;

int                    string_ctor(String, va_list *);
int                    string_dtor();

extern char            *__STRING;
extern t_module        __String;

#endif /* __STRING_H__ */
