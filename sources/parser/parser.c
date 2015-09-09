// ****************************************************************************
//                                                                            *
//                                 PARSER C                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include "stream.h"
#include "buffer.h"
#include "parser.h"
#include "utils.h"
#include "m_string.h"
#include "m_functions.h"
#include "built_in.h"

// ****************************************************************************
//                                                                            *
//                                  METHODS                                   *
//                                                                            *
// ****************************************************************************

static int      __set(Parser this, void *objet)
{
  if (objet == NULL)
    return (false);
  if (istype(objet, __BUFFER) == true)
    this->buffer = objet;
  else if (istype(objet, __STREAM) == true)
    this->stream = objet;
  else
    return (false);
  return (true);
}

static int      __reload_stream(Parser this)
{
  String        buffer = (String)(this->buffer);

  if (get(buffer, this->pos) != 0)
    return (true);
  if (this->stream == NULL
    || this->stream->read(this->stream, this->buffer) == false)
    return (false);
  return (true);
}

static int      __peek_char(Parser this, char c)
{
  char          *buffer;

  if (this->reload_stream(this) == false)
    return (-1);
  buffer = get(this->buffer, this->pos);
  if (buffer == NULL || *buffer != c)
    return (false);
  return (true);
}

static int      __read_eof(Parser this)
{
  return ((this->reload_stream(this) == false) ? true : false);
}

static int      __read_char(Parser this, char c)
{
  int           r = __peek_char(this, c);

  if (r != true)
    return (r);
  this->pos += 1;
  return (true);
}

static int      __save_state(Parser this)
{
  this->state = this->pos;
  return (true);
}

static char     *__get_state(Parser this)
{
  String        buffer = (String)this->buffer;
  unsigned int  len    = this->pos - this->state;
  char          *token = m_malloc(len + 1);

  if (token == NULL)
    return (NULL);
  m_strncpy(token, &((char *)buffer->content)[this->state], len);
  return (token);
}

static int      __read_range(Parser this, char c1, char c2)
{
  String        buffer = (String)this->buffer;
  char          c;
  int           r;

  if ((r = this->reload_stream(this)) != true)
    return (r);
  c = *((char *)get(buffer, this->pos));
  if (c1 > c || c > c2) {
    return (false);
  }
  this->pos += 1;
  return (true);
}

static int      __read_text(Parser this, char *string)
{
  char          *buff = ((String)this->buffer)->content;
  int           i = this->pos;
  int           r;

  if ((r = this->reload_stream(this)) != true)
    return (r);
  while (buff[i] != 0 && buff[i] == string[i - this->pos])
    i++;
  if (string[i - this->pos] != 0)
    return (false);
  this->pos = i;
  return (true);
}

static int      __read_integer(Parser this)
{
  if (this->read_range(this, '1', '9') != true
    || (this->read_char(this, '0') == true && this->read_range(this, '1', '9') == true)
    )
    return (false);
  while (this->read_range(this, '0', '9') == true);
  return (true);
}

static int      __is_identifiers(Parser this)
{
  if (this->read_range(this, 'a', 'z') != true
    || this->read_range(this, 'A', 'Z') != true
    || this->read_integer(this) != true
    || this->read_char(this, '-') != true
    || this->read_char(this, '_') != true
    )
    return (false);
  return (true);
}

static int      __read_identifiers(Parser this)
{
  if (__is_identifiers(this) == false)
    return (false);
  while (__is_identifiers(this) == true);
  return (true);
}

// ****************************************************************************
//                                                                            *
//                                    CLASS                                   *
//                                                                            *
// ****************************************************************************

char *__PARSER = "parser";

t_module __Parser = { sizeof(t_parser), parser_ctor, parser_dtor,
                      "parser",
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

static void     __methods(Parser this)
{
  this->reload_stream = __reload_stream;
  this->read_eof = __read_eof;
  this->save_state = __save_state;
  this->get_state = (pfct)__get_state;
  this->peek_char = (fct)__peek_char;
  this->read_text = __read_text;
  this->read_range = (fct)__read_range;
  this->read_char = (fct)__read_char;
  this->read_identifiers = __read_identifiers;
  this->read_integer = __read_integer;
  this->set = __set;
}

int             parser_ctor(Parser this, va_list *ap)
{
  void          *sources = va_arg(*ap, void *);

  this->stream = NULL;
  if (sources == NULL) {
    this->buffer = NULL;
  }
  else if (istype(sources, __BUFFER) == true)
    {
      this->buffer = sources;
    }
  else if (istype(sources, __STREAM) == true)
    {
      this->stream = sources;
      if ((this->buffer = new(__Buffer)) == NULL)
        return (false);
    }
  this->pos = 0;
  this->state = 0;
  __methods(this);
  return (true);
}

int           parser_dtor(Parser this)
{
  delete(this->buffer);
  return (true);
}
