// ****************************************************************************
//                                                                            *
//                                 BUFFER C                                   *
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
#include "buffer.h"
#include "m_string.h"

// ****************************************************************************
//                                                                            *
//                                  METHODS                                   *
//                                                                            *
// *****************************************************************************

static int      __concat(Buffer this, char *str, int str_len)
{
  String        _this = (String)this;
  int           new_len;

  if (str_len == -1)
    str_len = m_strlen(str, "");
  new_len = _this->len + str_len;
  _this->content = m_realloc(_this->content, new_len + 1);
  m_strncpy(&((char *)_this->content)[_this->len], str, str_len);
  _this->len = new_len;
  return (true);
}

static int      __bufferized(Buffer this, char *fmt, ...)
{
  String        _this = (String)this;
  va_list       ap;
  char          *str;
  int           str_len;

  va_start(ap, fmt);
  str = NULL;
  str_len = vasprintf(&str, fmt, ap);
  fprintf(stderr, "-- str %s\n", str);
  this->concat(this, str, str_len);
  free(str);
  va_end(ap);
  return (true);
}

// ****************************************************************************
//                                                                            *
//                                    CLASS                                   *
//                                                                            *
// ****************************************************************************

char *__BUFFER = "buffer";

t_module __Buffer =   { sizeof(t_buffer), buffer_ctor, buffer_dtor,
                        "buffer",
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                      };

// ****************************************************************************
//                                                                            *
//                                  CTOR/DTOR                                 *
//                                                                            *
// ****************************************************************************

static void    __methods(Buffer this)
{
  this->bufferized  = (fct)__bufferized;
  this->concat      = (fct)__concat;
}

int            buffer_ctor(Buffer this)
{
  if (super(this, __String, "") == false)
    return (false);
  __methods(this);
  return (true);
}

int            buffer_dtor(Buffer this)
{
  string_dtor(this);
  return (true);
}
