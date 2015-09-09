// ****************************************************************************
//                                                                            *
//                                M_STRDUP C                                  *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <string.h>
#include <stdio.h>

#include "m_functions.h"

char    *m_strndup(char *string, unsigned int len)
{
  char  *new_ptr;

  if (string == NULL)
    return (NULL);
  if (len == 0)
    {
      new_ptr = m_malloc(1);
      new_ptr[0] = 0;
      return (new_ptr);
    }
  if ((new_ptr = strndup(string, len)) == NULL)
    {
      perror("Error strndup");
      return (NULL);
    }
  return (new_ptr);
}

char    *m_strdup(char *string)
{
  return (m_strndup(string, m_strlen(string, "")));
}

char    *m_sstrdup(char *string, char *sep)
{
  return (m_strndup(string, m_strlen(string, sep)));
}
