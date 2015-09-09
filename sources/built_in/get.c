// ****************************************************************************
//                                                                            *
//                                   GET C                                    *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>

#include "modulaire.h"
#include "utils.h"

Objet       get(Objet ptr, unsigned int index)
{
  t_module  *module;

  if (ptr == NULL)
    return (false);
  module = (t_module *)ptr;
  return (module->get(ptr, index));
}
