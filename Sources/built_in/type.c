// ****************************************************************************
//                                                                            *
//                                  TYPE C                                    *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>

#include "utils.h"
#include "modulaire.h"
#include "m_functions.h"

char  *type(t_module *objet)
{
  if (objet == NULL)
    return (NULL);
  return (objet->type);
}

int   istype(t_module *objet, char *type_name)
{
  return (m_strcmp(type(objet), type_name) == 0 ? true : false);
}
