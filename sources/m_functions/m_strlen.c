// ****************************************************************************
//                                                                            *
//                                M_STRLEN C                                  *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>

#include "m_functions.h"

int    m_strlen(char *str, char *sep)
{
  int  i = 0;

  if (str == NULL)
    return (0);
  while (str[i] != 0 && m_find(sep, str[i], NULL) == -1)
    i++;
  return (i);
}
