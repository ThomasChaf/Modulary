// ****************************************************************************
//                                                                            *
//                                  LISTE H                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// *****************************************************************************

#ifndef __LISTE_H__
#define __LISTE_H__

#include "modulaire.h"
#include "utils.h"

typedef struct        s_liste_node
{
  Objet               content;
  struct s_liste_node *next;
  struct s_liste_node *prev;
}                     t_liste_node;

typedef struct        s_liste
{
  t_module            module;
  t_liste_node        *head;
  unsigned int        len;
  fct                 push_back;
  fct                 push_front;
  pfct                find;
  pfct                pop;
  fct                 delete;
  fct                 delete_all;
}                     t_liste;

typedef t_liste *     Liste;

int                   liste_ctor(Liste);
int                   liste_dtor();

extern char           *__LISTE;
extern t_module       __Liste;

#define push_back(x, y) (((Liste)x)->push_back(x, y))
#define push_front(x, y) (((Liste)x)->push_front(x, y))
#define pop(x) (((Liste)x)->pop(x))


#endif /* __LISTE_H__ */
