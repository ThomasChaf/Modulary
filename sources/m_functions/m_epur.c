// ****************************************************************************
//                                                                            *
//                                 M_EPUR H                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>

#include "utils.h"
#include "m_functions.h"

int     m_epur(char *str, char *to_epur, int hinib[][3])
{
  int   i;
  int   j;

  i = 0;
  j = 0;
  m_init_hinib(hinib);
  while (str[i] != 0)
    {
      if (m_hinib(hinib, str, i) == true || m_find(to_epur, str[i], NULL) == -1)
        str[j++] = str[i];
      i++;
    }
  str[j] = 0;
  return (j);
}
