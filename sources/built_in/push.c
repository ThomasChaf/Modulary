// ****************************************************************************
//                                                                            *
//                                  PUSH C                                    *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>

#include "modulaire.h"
#include "utils.h"

int           push(Objet ptr, Objet to_push)
{
  t_module    *module;

  if (ptr == NULL)
    return (false);
  module = (t_module *)ptr;
  return (module->push(ptr, to_push));
}
