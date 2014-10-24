// ****************************************************************************
//                                                                            *
//                                 STREAM C                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// *****************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdarg.h>

#include "m_functions.h"
#include "utils.h"
#include "stream.h"
#include "m_string.h"
#include "buffer.h"
#include "iter.h"
#include "built_in.h"

// ****************************************************************************
//                                                                            *
//                                  METHODS                                   *
//                                                                            *
// ****************************************************************************

static int      __cout(Stream this, char *fmt, ...)
{
  va_list       ap;

  va_start(ap, fmt);
  vdprintf(this->fd, fmt, ap);
  va_end(ap);
  if (this->fd == 1)
    fflush(stdout);
  return (true);
}

static int      __cin(Stream this, Buffer buff)
{
  int           ret;
  char          buffer[4096];

  if (this->eof == true || buff == NULL
    || (ret = m_read(this->fd, buffer, 4096)) <= 0)
    {
      this->eof = true;
      return (false);
    }
  this->eof = (ret != 4096 ? true : false);
  if (buffer[ret - 1] == '\n')
    ret -= 1;
  buffer[ret] = 0;
  buff->concat(buff, buffer, ret);
  return (true);
}

// ****************************************************************************
//                                                                            *
//                            BUILT_IN METHODS                                *
//                                                                            *
// ****************************************************************************

static void       __str(Stream this)
{
  printf("Stream from fd: %d\n", this->fd);
}

// ****************************************************************************
//                                                                            *
//                                    CLASS                                   *
//                                                                            *
// ****************************************************************************

char *__STREAM = "stream";

t_module __Stream = { sizeof(t_stream), stream_ctor, stream_dtor,
                      "stream",
                      0,
                      0,
                      __str,
                      0,
                      0,
                      0
                    };

// ****************************************************************************
//                                                                            *
//                                  CTOR/DTOR                                 *
//                                                                            *
// ****************************************************************************

static void     __methods(Stream this)
{
  this->cout = (fct)__cout;
  this->cin = __cin;
}

int             stream_ctor(Stream this, va_list *ap)
{
  if ((this->fd = va_arg(*ap, int)) == -1)
    return (false);
  this->eof = false;
  __methods(this);
  return (true);
}

int             stream_dtor(Stream this)
{
  if (this->fd > 2)
    close(this->fd);
  return (true);
}
