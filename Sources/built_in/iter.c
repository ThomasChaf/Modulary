// ****************************************************************************
//                                                                            *
//                                  ITER C                                    *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>

#include "modulaire.h"
#include "iter.h"

Iter        iter(Objet ptr)
{
  t_module  *module;

  if (ptr == NULL)
    return (NULL);
  module = (t_module *)ptr;
  return (module->iter(ptr));
}
