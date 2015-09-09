// ****************************************************************************
//                                                                            *
//                                  NEXT C                                    *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>

#include "modulaire.h"
#include "iter.h"

void  *next(Iter ptr)
{
  if (ptr == NULL)
    return (NULL);
  return (ptr->next(ptr));
}
