// ****************************************************************************
//                                                                            *
//                                   SUM C                                    *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>

#include "modulaire.h"

Objet       sum(Objet ptr1, Objet ptr2)
{
  t_module  *module;

  if (ptr1 == NULL)
    return (NULL);
  module = (t_module *)ptr1;
  return (module->sum(ptr1, ptr2));
}
