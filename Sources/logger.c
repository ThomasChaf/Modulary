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

static Logger     __get_logger(int ctor)
{
  static Logger   logger = NULL;

  if (ctor && !logger)
    logger = new(__Logger);
  else if (!ctor)
    delete(logger);
  return (logger);
}

Logger            get_logger()
{
  return __get_logger(true);
}

void              delete_logger()
{
  __get_logger(false);
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

int            logger_ctor(Logger this)
{
  int          fd;

  fd = (DEFAULT_LOG? m_create(DEFAULT_LOG) : 1);
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
