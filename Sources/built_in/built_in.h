// ****************************************************************************
//                                                                            *
//                                BUILT_IN H                                  *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#ifndef __BUILT_IN__
#define __BUILT_IN__

unsigned int    len(Objet);
Objet           sum(Objet, Objet);
void            str(Objet);
Iter            next(Iter);
Iter            iter(Objet);
int             push(Objet, Objet);
Objet           get(Objet, unsigned int);
char            *type(t_module *);
int             istype(t_module *, char *);

#endif /* __BUILT_IN__ */
