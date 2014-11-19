// ****************************************************************************
//                                                                            *
//                                   JSON C                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "m_functions.h"
#include "stream.h"
#include "buffer.h"
#include "parser.h"
#include "array.h"
#include "json.h"
#include "built_in.h"

// ****************************************************************************
//                                                                            *
//                                  METHODS                                   *
//                                                                            *
// ****************************************************************************

static t_jnode  *json_decode(Json this)
{
  this->head = __json_decode(this);
  return (this->head);
}

static void     *json_get(Json this, String needle, t_jnode *node)
{
  if (needle == NULL)
    return (NULL);
  return (__json_get(this, needle->split(needle, JSON_SEP, NULL), 0, (node == NULL ? this->head : node)));
}

static void     json_encode(Json this)
{
  Parser        _this = (Parser)this;

  if (_this->stream == NULL)
    return ;
  __json_encode(this, _this->stream, this->head, 0);
  _this->stream->write(_this->stream, "\n");
}

// ****************************************************************************
//                                                                            *
//                             PARENTS METHODS                                *
//                                                                            *
// *****************************************************************************

static int      __reload_stream(Parser this)
{
  String        buffer = (String)(this->buffer);

  if (get(buffer, this->pos) != 0)
    return (true);
  if (this->stream->read(this->stream, buffer) == false)
    return (false);
  buffer->epur(buffer, "\n \t", &json_hinib[2]);
  return (true);
}

static int      __read_hexa(Parser this)
{
  if (this->read_range(this, 'a', 'f') != true
    && this->read_range(this, 'A', 'F') != true
    && this->read_range(this, '0', '9') != true
    )
    return (false);
  return (true);
}

static int      __read_hexadig(Parser this)
{
  int           save = this->pos;

  if (this->read_char(this, HEXDIG) != true
    || __read_hexa(this) != true
    || __read_hexa(this) != true
    || __read_hexa(this) != true
    || __read_hexa(this) != true
    ) {
      this->pos = save;
      return (false);
    }
  return (true);
}

static int      __read_escape_char(Parser this)
{
  if (this->read_char(this, QUOTATION_MARK) != true
    && this->read_char(this, REVERSE_SOLIDUS) != true
    && this->read_char(this, SOLIDUS) != true
    && this->read_char(this, BACKSPACE) != true
    && this->read_char(this, FORM_FEED) != true
    && this->read_char(this, LINE_FEED) != true
    && this->read_char(this, CARRIAGE_RETURN) != true
    && this->read_char(this, TAB) != true
    && __read_hexadig(this) != true
    )
    return (false);
  return (true);
}

// unescaped = %x20-21 / %x23-5B / %x5D-10FFFF
static int      __read_unscape_char(Parser this)
{
  if (this->read_range(this, 0x20, 0x21) != true
    && this->read_range(this, 0x23, 0x5b) != true
    && this->read_range(this, 0x5d, 0x7e) != true)
    {
      return (false);
    }
  return (true);
}

static int      __read_json_char(Parser this)
{
  int           save = this->pos;

  if (__read_unscape_char(this) == true)
    return (true);
  if (this->read_char(this, REVERSE_SOLIDUS) == true
      && __read_escape_char(this) == true)
    return (true);
  this->pos = save;
  return (false);
}

static int      __read_string(Parser this)
{
  if (this->read_char(this, QUOTATION_MARK) != true)
    return (false);
  while (__read_json_char(this) == true);
  if (this->read_char(this, QUOTATION_MARK) != true)
    return (false);
  return (true);
}

static int      __read_digit(Parser this)
{
  if (this->read_range(this, '1', '9') == true
    ||  (this->read_char(this, '0') == true
        && this->read_range(this, '1', '9') != true
        )
    ) {
      while (this->read_range(this, '0', '9') == true);
      return (true);
    }
  return (false);
}

static int      __read_exp(Parser this)
{
  if (this->read_char(this, 'e') != true
    && this->read_char(this, 'E') != true)
    return (false);
  if (this->read_char(this, '-') != true)
    this->read_char(this, '+');
  if (this->read_range(this, '0', '9') != true)
    return (false);
  while (this->read_range(this, '0', '9') == true);
  return (true);
}

static int      __read_integer(Parser this)
{
  int           save = this->pos;

  this->read_char(this, J_MINUS);
  if (__read_digit(this) != true) {
    this->pos = save;
    return (false);
  }
  save = this->pos;
  if (this->read_char(this, J_DECIMAL_POINT) == true && __read_digit(this) != true)
    this->pos = save;
  save = this->pos;
  if (__read_exp(this) != true)
    this->pos = save;
  return (true);
}

static int      __read_identifiers(Parser this)
{
  if (this->read_text(this, J_TRUE) != true
    && this->read_text(this, J_FALSE) != true
    && this->read_text(this, J_NULL) != true
    && this->read_integer(this) != true
    && __read_string(this) != true
    )
    return (false);
  return (true);
}

// ****************************************************************************
//                                                                            *
//                                    CLASS                                   *
//                                                                            *
// *****************************************************************************

char *__JSON = "json";

t_module __Json = { sizeof(t_json), json_ctor, json_dtor,
                    "json",
                    0,
                    0,
                    0,
                    0,
                    0,
                    0
                  };

// ****************************************************************************
//                                                                            *
//                                  CTOR/DTOR                                 *
//                                                                            *
// ****************************************************************************

static void     json_free(t_json *this, t_jnode *node)
{
  __json_free(this, node);
}

void            __methods(Json this)
{
  Parser        parent = (Parser)this;

  this->json_get = json_get;
  this->json_decode = json_decode;
  this->json_encode = json_encode;
  this->json_free = json_free;
  this->read_string = __read_string;
  parent->reload_stream = __reload_stream;
  parent->read_identifiers = __read_identifiers;
  parent->read_integer = __read_integer;
}

int             json_ctor(Json this, va_list *ap)
{
  if ((super(this, __Parser, va_arg(*ap, Stream))) == false)
    return (false);
  this->head = NULL;
  __methods(this);
  return (true);
}

int             json_dtor(Json this)
{
  this->json_free(this, this->head);
  parser_dtor(this);
  return (true);
}
