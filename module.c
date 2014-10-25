// ****************************************************************************
//                                                                            *
//                                 MODULE C                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "modulaire.h"
#include "m_functions.h"

static void   built_in(t_module *obj, t_module new_module)
{
  obj->len  = (obj->len  == 0 ? new_module.len  : obj->len);
  obj->sum  = (obj->sum  == 0 ? new_module.sum  : obj->sum);
  obj->str  = (obj->str  == 0 ? new_module.str  : obj->str);
  obj->iter = (obj->iter == 0 ? new_module.iter : obj->iter);
  obj->push = (obj->push == 0 ? new_module.push : obj->push);
  obj->get  = (obj->get  == 0 ? new_module.get  : obj->get);
}

int           super(void *obj, t_module new_module, ...)
{
  va_list     ap;
  int         r;

  va_start(ap, new_module);
  r = new_module.c_tor(obj, &ap);
  va_end(ap);
  built_in(obj, new_module);
  return (r);
}

void          *new(t_module new_module, ...)
{
  void        *obj;
  va_list     ap;

  if ((obj = m_malloc(new_module.size)) == NULL)
    return (NULL);
  va_start(ap, new_module);
  memcpy(obj, &new_module, sizeof(t_module));
  if (new_module.c_tor(obj, &ap) == 0)
  {
    free(obj);
    obj = NULL;
  }
  va_end(ap);
  return (obj);
}

void          delete(void *module)
{
  if (module == NULL)
    return ;
  ((t_module *)module)->d_tor(module);
  free(module);
}
