// ****************************************************************************
//                                                                            *
//                                  LISTE C                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// *****************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "m_functions.h"
#include "utils.h"
#include "liste.h"
#include "iter.h"

// ****************************************************************************
//                                                                            *
//                                  METHODS                                   *
//                                                                            *
// *****************************************************************************

static int          __delete_all(Liste this)
{
  t_liste_node      *tmp = this->head;

  while (tmp != NULL)
  {
    delete(tmp->content);
    tmp = tmp->next;
  }
  this->len = 0;
  return (true);
}

static int          __delete(Liste this, void *elem)
{
  t_liste_node      *tmp  = this->head;
  t_liste_node      *prev = NULL;

  while (tmp != NULL)
  {
    if (tmp->content == elem)
    {
      if (tmp == this->head)
        this->head = tmp->next;
      else
        prev->next = tmp->next;
      this->len -= 1;
      delete(tmp->content);
      free(tmp);
      return (true);
    }
    prev = tmp;
    tmp = tmp->next;
  }
  return (false);
}

static int          __push_front(Liste this, void *elem)
{
  t_liste_node      *tmp;
  t_liste_node      *new_node;

  if (elem == NULL || (new_node = m_malloc(sizeof(t_liste_node))) == NULL)
    return (false);
  this->len += 1;
  new_node->content = elem;
  new_node->prev = NULL;
  new_node->next = this->head;
  this->head = new_node;
  return (true);
}

static int          __push_back(Liste this, Objet elem)
{
  t_liste_node      *tmp;
  t_liste_node      *new_node;

  if (elem == NULL || (new_node = m_malloc(sizeof(t_liste_node))) == NULL)
    return (false);
  this->len += 1;
  new_node->content = elem;
  new_node->prev = NULL;
  new_node->next = NULL;
  if (this->head == NULL)
  {
    this->head = new_node;
    return (true);
  }
  tmp = this->head;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = new_node;
  return (true);
}

static Objet        __pop(Liste this)
{
  Objet             content;
  t_liste_node      *tmp = this->head;

  if (this->head == NULL)
    return (NULL);
  this->len -= 1;
  content = tmp->content;
  this->head = this->head->next;
  free(tmp);
  return (content);
}

static Objet        __find(Liste this, void *pattern, fct comparator)
{
  t_liste_node      *tmp = this->head;

  while (tmp)
  {
    if (comparator(tmp->content, pattern) == true)
      return (tmp->content);
    tmp = tmp->next;
  }
  return (NULL);
}

// ****************************************************************************
//                                                                            *
//                            BUILT_IN METHODS                                *
//                                                                            *
// *****************************************************************************

static int            __push(Liste this, Objet ptr)
{
  return (__push_back(this, ptr));
}

static Objet          __get(Liste this, unsigned int index)
{
  t_liste_node        *tmp = this->head;
  unsigned int        i = 0;


  if (index >= this->len)
    return (NULL);
  while (tmp)
  {
    if (i == index)
      return (tmp->content);
    tmp = tmp->next;
    i++;
  }
  return (NULL);
}

static unsigned int   __len(Liste this)
{
  return (this->len);
}

static Iter           __next(Iter iter)
{
  if (iter->current == NULL || ((t_liste_node *)iter->current)->next == NULL)
    {
      free(iter);
      return (NULL);
    }
  iter->current = ((t_liste_node *)iter->current)->next;
  iter->content = ((t_liste_node *)iter->current)->content;
  return (iter);
}

static Iter           __iter(Liste this)
{
  Iter                iter;

  if (this == NULL || this->head == NULL)
    return (NULL);
  iter = m_malloc(sizeof(t_iter));
  iter->objet = this;
  iter->current = this->head;
  iter->content = ((t_liste_node *)iter->current)->content;
  iter->next = __next;
  return (iter);
}

static Objet          __sum(Liste l1, Liste l2)
{
  Liste               this = new(__Liste);
  Iter                it = __iter(l1);

  while (it)
    {
      push_back(this, it->content);
      it = __next(it);
    }
  it = __iter(l2);
  while (it)
    {
      push_back(this, it->content);
      it = __next(it);
    }
  return (this);
}

static void           __to_string(Liste this)
{
  t_liste_node        *tmp = this->head;

  while (tmp)
  {
    printf("%s\n", (char *)(tmp->content));
    tmp = tmp->next;
  }
}

// ****************************************************************************
//                                                                            *
//                                    CLASS                                   *
//                                                                            *
// *****************************************************************************

char *__LISTE = "liste";

t_module __Liste =  { sizeof(t_liste),  liste_ctor, liste_dtor,
                      "liste",
                      __len,
                      __sum,
                      __to_string,
                      __iter,
                      __push,
                      __get
                    };

// ****************************************************************************
//                                                                            *
//                                  CTOR/DTOR                                 *
//                                                                            *
// ****************************************************************************

static void           __methods(Liste this)
{
  this->push_back   = __push_back;
  this->push_front  = __push_front;
  this->find        = __find;
  this->pop         = __pop;
  this->delete      = __delete;
  this->delete_all  = __delete_all;
}

int                   liste_ctor(Liste this)
{
  this->head = NULL;
  this->len = 0;
  __methods(this);
  return (true);
}

int                   liste_dtor(Liste this)
{
  t_liste_node        *tmp;

  while (this->head)
  {
    tmp = this->head;
    this->head = this->head->next;
    free(tmp);
  }
  return (true);
}
