#ifndef __STREAM_H__
#define __STREAM_H__

#include <stdarg.h>

#include "modulaire.h"
#include "m_string.h"

typedef struct         s_stream
{
  t_module             module;
  int                  fd;
  int                  eof;
  fct                  read;
  fct                  write;
}                      t_stream;

typedef t_stream *      Stream;

int                    stream_ctor(Stream, va_list *);
int                    stream_dtor();

extern char            *__STREAM;
extern t_module        __Stream;

#endif /* __STREAM_H__ */
