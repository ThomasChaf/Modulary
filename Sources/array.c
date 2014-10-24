// ****************************************************************************
//                                                                            *
//                                  ARRAY C                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// *****************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "m_functions.h"
#include "utils.h"
#include "array.h"
#include "iter.h"

// ****************************************************************************
//                                                                            *
//                                  METHODS                                   *
//                                                                            *
// *****************************************************************************

static int          __put(Array this, unsigned int index, Objet ptr)
{
  if (index >= this->len)
    return (false);
  this->content[index] = ptr;
  return (true);
}

// ****************************************************************************
//                                                                            *
//                            BUILT_IN METHODS                                *
//                                                                            *
// *****************************************************************************

static int          __push(Array this, Objet ptr)
{
  if (this->current >= this->len)
    return (false);
  return (__put(this, this->current++, ptr));
}

static Objet        __get(Array this, unsigned int index)
{
  if (index >= this->len)
    return (NULL);
  return (this->content[index]);
}

static unsigned int __len(Array this)
{
  if (this == NULL)
    return (0);
  return (this->len);
}

static Iter         __next(Iter iter)
{
  int               current = *((int *)iter->current) + 1;

  if (current >= ((Array)iter->objet)->len)
    {
      free(iter);
      return (NULL);
    }
  *((int *)iter->current) = current;
  iter->content = ((Array)iter->objet)->content[current];
  return (iter);
}

static Iter         __iter(Array this)
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
  iter->content = ((Array)iter->objet)->content[current];
  iter->next = __next;
  return (iter);
}

static Objet        __sum(Array l1, Array l2)
{
  Array             this = new(__Array, __len(l1) + __len(l2));
  Iter              it = __iter(l1);
  int               i = 0;

  while (it)
    {
      this->content[i++] = it->content;
      it = __next(it);
    }
  it = __iter(l2);
  while (it)
    {
      this->content[i++] = it->content;
      it = __next(it);
    }
  this->content[i] = NULL;
  return (this);
}

static void         __str(Array this)
{
  int               i = 0;

  while (i < this->len)
  {
    printf("%s\n", (char *)(this->content[i++]));
  }
}

// ****************************************************************************
//                                                                            *
//                                    CLASS                                   *
//                                                                            *
// ****************************************************************************

char *__ARRAY = "array";

t_module __Array =  { sizeof(t_array),  array_ctor, array_dtor,
                      "array",
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

int            array_ctor(Array this, va_list *ap)
{
  int          i = 0;

  this->len = va_arg(*ap, unsigned int);
  this->content = m_malloc(sizeof(Objet) * (this->len + 1));
  this->current = 0;
  while (i < (this->len + 1))
    this->content[i++] = NULL;
  return (true);
}

int            array_dtor(Array this)
{
  free(this->content);
  return (true);
}
