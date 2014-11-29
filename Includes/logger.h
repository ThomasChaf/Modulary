// ****************************************************************************
//                                                                            *
//                                 LOGGER H                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  28  /  09  /  2014  *
// ****************************************************************************

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdarg.h>

#include "modulaire.h"
#include "utils.h"

#define DEFAULT_LOG (NULL)

typedef struct    s_logger
{
  t_module        module;
  fct             error;
  fct             info;
  Stream          stream;
}                 t_logger;

typedef t_logger * Logger;

Logger            get_logger();
void              delete_logger();
int               logger_ctor(Logger);
int               logger_dtor();

extern char       *__LOGGER;

#define LOG_INFO(fmt, ...) ((get_logger())->info(get_logger(), fmt, ## __VA_ARGS__))
#define LOG_ERROR(fmt, ...) ((get_logger())->error(get_logger(), fmt, ## __VA_ARGS__))

#endif /* __LOGGER_H__ */
