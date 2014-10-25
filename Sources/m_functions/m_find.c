// ****************************************************************************
//                                                                            *
//                                 M_FIND C                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include "m_functions.h"
#include "utils.h"

int    same_hinib(char *str, int i)
{
  int  nb;

  nb = 0;
  while (i > 0 && str[i - 1] == '\\')
    {
      nb++;
      i--;
    }
  return (nb % 2 == 0 ? 1 : 0);
}

int    m_init_hinib(int hinib[][3])
{
  int  i;

  if (hinib == NULL)
    return (0);
  i = 0;
  while (hinib[i][1] != 0)
    hinib[i++][0] = 0;
  return (0);
}

int    m_hinib(int hinib[][3], char *str, int index)
{
  char c = str[index];
  int  i = 0;
  int  begin = false;

  if (hinib == NULL)
    return (false);
  while (hinib[i][1] != 0)
    {
      if (hinib[i][0] != 0)
        {
          if (hinib[i][1] == c && (hinib[i][1] == hinib[i][2] && same_hinib(str, index) == 1))
            hinib[i][0] = (hinib[i][0] == 0);
          else if (hinib[i][1] == c)
            hinib[i][0] += 1;
          else if (hinib[i][2] == c)
          {
            hinib[i][0] -= 1;
            begin = true;
          }
          return (hinib[i][0] == 0 && begin != true ? false : true);
        }
      i++;
    }
  i = 0;
  while (hinib[i][1] != 0)
    {
      if (hinib[i][1] == c && (hinib[i][1] == hinib[i][2] && same_hinib(str, index) == 1))
        {
          hinib[i][0] = (hinib[i][0] == 0);
          begin = hinib[i][0];
        }
      else if (hinib[i][1] == c)
        {
          hinib[i][0] += 1;
          begin = true;
        }
      else if (hinib[i][2] == c)
        hinib[i][0] -= 1;
      i++;
    }
  i = 0;
  while (hinib[i][1] != 0)
    {
      if (hinib[i][0] != 0 && (hinib[i][0] != 1 || begin != true))
        return (true);
      i++;
    }
  return (false);
}

int    m_find(char *sep, char c, int hinib[][3])
{
  int  i = 0;

  if (sep == NULL)
    return (-1);
  m_init_hinib(hinib);
  while (sep[i] != 0)
    {
      if (m_hinib(hinib, sep, i) == false && sep[i] == c)
        return (i);
      i++;
    }
  return (-1);
}

int    m_count_word(char *str, char *sep, int hinib[][3])
{
  int  nb_word = 0;
  int  i = 0;

  if (str == NULL)
    return (-1);
  m_init_hinib(hinib);
  while (str[i])
    {
      if (m_hinib(hinib, str, i) == false && m_find(sep, str[i], NULL) == -1)
        {
          if (i == 0 || m_find(sep, str[i - 1], NULL) != -1)
            nb_word++;
        }
      i++;
    }
  return (nb_word);
}
