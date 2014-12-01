// ****************************************************************************
//                                                                            *
//                                 PARSER H                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdlib.h>

typedef struct    s_parser
{
  t_module        module;
  Stream          stream;
  Buffer          buffer;
  int             pos;
  int             state;
  fct             set;
  fct             reload_stream;
  fct             read_eof;
  fct             peek_char;
  fct             read_text;
  fct             read_range;
  fct             read_char;
  fct             read_identifiers;
  fct             read_digit;
  fct             read_integer;
  fct             save_state;
  pfct            get_state;
}                 t_parser;

typedef t_parser * Parser;

int               parser_ctor(Parser, va_list *);
int               parser_dtor();

extern char *     __PARSER;
extern t_module   __Parser;

#endif /* __PARSER_H__ */
