// ****************************************************************************
//                                                                            *
//                                   ITER H                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// *****************************************************************************

#ifndef __ITER_H__
#define __ITER_H__

#include "modulaire.h"

typedef struct   s_iter
{
  void           *objet;
  void           *content;
  void           *current;
  struct s_iter  *(*next)();
}                t_iter;

typedef t_iter * Iter;

#endif /* __ITER_H__ */
