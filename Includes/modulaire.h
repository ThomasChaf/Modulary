#ifndef __MODULAIRE_H__
#define __MODULAIRE_H__

#include <stdarg.h>

#include "iter.h"

typedef void * Objet;
typedef int    (*fct)();
typedef Objet  (*pfct)();

typedef struct  s_module
{
  unsigned int  size;
  int           (*c_tor)();
  int           (*d_tor)();
  char          *type;
  unsigned int  (*len)();
  Objet         (*sum)();
  char          *(*str)();
  Iter          (*iter)();
  int           (*push)();
  Objet         (*get)();
}               t_module;

int             super(Objet, t_module, ...);
Objet           new(t_module, ...);
void            delete(void *);

#endif /* __MODULAIRE_H__ */
