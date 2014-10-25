// ****************************************************************************
//                                                                            *
//                                M_STRCAT C                                  *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>

#include "m_functions.h"

char    *m_strcat(char *string1, char *string2)
{
  int   len1 = m_strlen(string1, "");
  int   len2 = m_strlen(string2, "");
  char  *ptr = m_malloc(len1 + len2 + 1);

  if (ptr == NULL)
    return (NULL);
  m_strncpy(ptr, string1, len1);
  m_strncpy(&ptr[len1], string2, len2);
  ptr[len1 + len2] = 0;
  return (ptr);
}
