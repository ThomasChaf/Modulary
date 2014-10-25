// ****************************************************************************
//                                                                            *
//                                M_STRCPY C                                  *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>
#include <string.h>

#include "m_functions.h"

void    m_strncpy(char *dest, const char *src, unsigned int len)
{
  int   i = 0;

  if (dest == NULL || src == NULL)
    return ;
  while (src[i] != 0 && i < len)
    {
      dest[i] = src[i];
      i++;
    }
  dest[i] = 0;
}

void    m_strcpy(char *dest, char *src)
{
  m_strncpy(dest, src, m_strlen(src, ""));
}
