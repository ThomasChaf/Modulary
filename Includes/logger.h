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

typedef struct    s_logger
{
  t_module        module;
  fct             error;
  fct             info;
  Stream          stream;
}                 t_logger;

typedef t_logger * Logger;

Logger            __get_logger(int, char *);
Logger            get_logger();
void              delete_logger();
int               logger_ctor(Logger, va_list *);
int               logger_dtor();

extern char       *__LOGGER;

#define DEFAULT_LOG(path) (get_logger(true, path))

#define LOG_INFO(fmt, ...) ((get_logger(true, NULL))->info(get_logger(true, NULL), fmt, ## __VA_ARGS__))
#define LOG_ERROR(fmt, ...) ((get_logger(true, NULL))->error(get_logger(true, NULL), fmt, ## __VA_ARGS__))

#endif /* __LOGGER_H__ */
