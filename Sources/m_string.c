// ****************************************************************************
//                                                                            *
//                                 STRING C                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// *****************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "modulaire.h"
#include "m_functions.h"
#include "built_in.h"
#include "utils.h"
#include "m_string.h"
#include "array.h"
#include "iter.h"

// ****************************************************************************
//                                                                            *
//                                  METHODS                                   *
//                                                                            *
// ****************************************************************************

static int          __epur(String this, char *to_epur, int hinib[][3])
{
  if (this->content == NULL)
    return (false);
  this->len = m_epur(this->content, to_epur, hinib);
  return (true);
}

static int          __set(String this, unsigned int index, char c)
{
  if (index >= this->len)
    return (false);
  ((char *)this->content)[index] = c;
  return (true);
}

static Objet        __split(String this, char *sep, int hinib[][3])
{
  char              *str = this->content;
  Array             array = new(__Array, m_count_word(str, sep, hinib));
  int               i = 0;

  if (array == NULL)
    return (NULL);
  m_init_hinib(hinib);
  while (str[i])
  {
    if (m_hinib(hinib, str, i) == false && m_find(sep, str[i], NULL) == -1)
    {
      if (i == 0 || m_find(sep, str[i - 1], NULL) != -1)
        push(array, m_sstrdup(&str[i], sep));
    }
    i++;
  }
  return (array);
}

// ****************************************************************************
//                                                                            *
//                            BUILT_IN METHODS                                *
//                                                                            *
// ****************************************************************************

static int          __push(String this, char *ptr)
{
  this->content = m_strdup(ptr);
  this->len = m_strlen(this->content, "");
  return (this->content != NULL ? true : false);
}

static Objet        __get(String this, unsigned int index)
{
  if (index >= this->len)
    return (NULL);
  return (&this->content[index]);
}

static unsigned int __len(String this)
{
  if (this == NULL)
    return (0);
  return (this->len);
}

static Iter         __next(Iter iter)
{
  int               current = *((int *)iter->current) + 1;

  if (current >= ((String)iter->objet)->len)
    {
      free(iter);
      return (NULL);
    }
  *((int *)iter->current) = current;
  iter->content = &((char *)((String)iter->objet)->content)[current];
  return (iter);
}

static Iter         __iter(String this)
{
  void              *ptr;
  Iter              iter;
  int               current = 0;

  if (this == NULL || this->len == 0
    || (ptr = m_malloc(sizeof(t_iter) + sizeof(int))) == NULL)
    return (NULL);
  iter = (Iter)ptr;
  iter->objet = this;
  iter->current = ptr + sizeof(t_iter);
  *((int *)iter->current) = current;
  iter->content = &((char *)((String)iter->objet)->content)[current];
  iter->next = __next;
  return (iter);
}

static Objet        __sum(String s1, String s2)
{
  String            this;
  char              *content;

  if (s1 == NULL || s2 == NULL
    || (content = m_strcat(s1->content, s2->content)) == NULL)
    return (NULL);
  this = new(__String, content);
  free(content);
  return (this);
}

static char         *__str(String this)
{
  return (this->content);
}

// ****************************************************************************
//                                                                            *
//                                    CLASS                                   *
//                                                                            *
// ****************************************************************************

char *__STRING = "string";

t_module __String = { sizeof(t_string), string_ctor, string_dtor,
                      "string",
                      __len,
                      __sum,
                      __str,
                      __iter,
                      __push,
                      __get
                    };

// ****************************************************************************
//                                                                            *
//                                  CTOR/DTOR                                 *
//                                                                            *
// ****************************************************************************

static void         __methods(String this)
{
  this->split       = __split;
  this->set         = (fct)__set;
  this->epur        = __epur;
}

int                 string_ctor(String this, va_list *ap)
{
  if ((this->content = m_strdup(va_arg(*ap, char *))) == NULL)
    return (false);
  this->len = m_strlen(this->content, "");
  __methods(this);
  return (true);
}

int                 string_dtor(String this)
{
  free(this->content);
  return (true);
}
