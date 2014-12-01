// ****************************************************************************
//                                                                            *
//                                 LOGGER C                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  28  /  09  /  2014  *
// ****************************************************************************

#include <stdarg.h>
#include <stdio.h>

#include "modulary.h"
#include "logger.h"

// ****************************************************************************
//                                                                            *
//                                  METHODS                                   *
//                                                                            *
// *****************************************************************************


int            __error(Logger this, char *fmt, ...)
{
  va_list       ap;

  va_start(ap, fmt);
  dprintf(this->stream->fd, "[ERROR] ");
  this->stream->va_write(this->stream, fmt, ap);
  va_end(ap);
  return (true);
}

int            __info(Logger this, char *fmt, ...)
{
  va_list       ap;

  va_start(ap, fmt);
  this->stream->va_write(this->stream, fmt, ap);
  va_end(ap);
  return (true);
}

// ****************************************************************************
//                                                                            *
//                                    CLASS                                   *
//                                                                            *
// ****************************************************************************

char *__LOGGER = "logger";

static t_module __Logger = { sizeof(t_logger), logger_ctor, logger_dtor,
  "logger",
  0,
  0,
  0,
  0,
  0,
  0
};

// ****************************************************************************
//                                                                            *
//                                  SINGLETON                                 *
//                                                                            *
// ****************************************************************************

Logger            get_logger(int ctor, char *path)
{
  static Logger   logger = NULL;

  if ((ctor && logger == NULL) || path)
    logger = new(__Logger, path);
  else if (!ctor)
  {
    delete(logger);
    logger = NULL;
  }
  return (logger);
}

// ****************************************************************************
//                                                                            *
//                                  CTOR/DTOR                                 *
//                                                                            *
// ****************************************************************************

static void    __methods(Logger this)
{
  this->error = (fct)__error;
  this->info = (fct)__info;
}

int            logger_ctor(Logger this, va_list *ap)
{
  char         *path = va_arg(*ap, char *);
  int          fd = (path == NULL ? 1 : m_create(path));

  if ((this->stream = new(__Stream, fd)) == NULL)
    return (false);
  __methods(this);
  return (true);
}

int           logger_dtor(Logger this)
{
  delete(this->stream);
  return (true);
}
