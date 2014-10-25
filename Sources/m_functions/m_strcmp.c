// ****************************************************************************
//                                                                            *
//                                M_STRCMP C                                  *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>
#include <string.h>

int  m_strcmp(char *str1, char *str2)
{
  if (str1 == NULL || str2 == NULL)
    return (-1);
  return (strcmp(str1, str2));
}
