// ****************************************************************************
//                                                                            *
//                                   STR C                                    *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>

#include "modulaire.h"

void        str(Objet ptr)
{
  t_module  *module;

  if (ptr == NULL)
    return ;
  module = (t_module *)ptr;
  module->str(ptr);
}
