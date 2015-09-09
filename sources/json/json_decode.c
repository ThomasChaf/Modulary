// ****************************************************************************
//                                                                            *
//                               JSON_DECODE C                                *
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

t_jnode *json_create_value(Json, t_jnode *);

void          *un_stringify(char *str)
{
  int         i = 0;
  int         end = m_strlen(str, "") - 1;

  if (str[0] == '"' && str[end] == '"')
  {
    while (i < end - 1)
    {
      str[i] = str[i + 1];
      i++;
    }
    str[i] = 0;
  }
  return (str);
}

t_jnode       *json_create_node(t_json *this, t_jnode *parent, t_jtype type)
{
  t_jnode     *tmp = m_malloc(sizeof(t_jnode));

  if (tmp == NULL)
    return (NULL);
  tmp->parent = parent;
  tmp->type = type;
  tmp->next = NULL;
  tmp->child = NULL;
  tmp->content = NULL;
  return (tmp);
}

t_jnode       *json_create_string(Json this, t_jnode *parent)
{
  Parser      _this = (Parser)this;
  char        *token;
  t_jnode     *tmp;

  _this->save_state(this);
  if (_this->read_identifiers(this) == false
    || (token = _this->get_state(this)) == NULL
    || (tmp = json_create_node(this, parent, J_STRING)) == NULL)
    return (NULL);
  tmp->content = un_stringify(token);
  return (tmp);
}

t_jnode       *json_create_object(Json this, t_jnode *parent)
{
  Parser      _this = (Parser)this;
  t_jnode     *head = NULL;
  t_jnode     *tmp;
  char        *key = NULL;

  if (_this->peek_char(_this, END_OBJECT) != true)
    while (head == NULL || (_this->read_char(_this, VALUE_SEPARATOR) == true))
      {
        _this->save_state(this);
        if (this->read_string(this) == false
          || (key = _this->get_state(this)) == NULL
          || (tmp = json_create_node(this, parent, J_OBJET)) == NULL)
          {
            fprintf(stderr, INVALID_KEY);
            return (NULL);
          }
        tmp->content = un_stringify(key);
        if (_this->read_char(_this, NAME_SEPARATOR) == false)
          {
            fprintf(stderr, NO_NAME_SEPARATOR);
            return (NULL);
          }
        if ((tmp->child = json_create_value(this, tmp)) == NULL)
          return (NULL);
        tmp->next = head;
        head = tmp;
      }
  else
    head = json_create_node(this, parent, J_OBJET);
  if (_this->read_char(_this, END_OBJECT) != true)
    {
      fprintf(stderr, UNCLOSED_OBJECT);
      return (NULL);
    }
  return (head);
}

t_jnode       *json_create_array(Json this, t_jnode *parent)
{
  Parser      _this = (Parser)this;
  t_jnode     *head = json_create_node(this, parent, J_ARRAY);
  int         i = 0;

  if (head == NULL ||
    (head->content = m_malloc(10 * sizeof(t_jnode *))) == NULL)
    return (NULL);
  if (_this->peek_char(_this, END_ARRAY) != true)
    while (i == 0 || _this->read_char(_this, VALUE_SEPARATOR) == true)
      {
        if (i % 10 == 0 && i != 0)
          head->content = m_realloc(head->content, 10 * (i / 10 + 1) * sizeof(t_jnode *));
        if ((((void **)head->content)[i] = json_create_value(this, head)) == NULL)
          return (NULL);
        i++;
      }
  ((void **)head->content)[i] = NULL;
  if (_this->read_char(_this, END_ARRAY) != true)
    {
      fprintf(stderr, UNCLOSED_ARRAY);
      return (NULL);
    }
  return (head);
}

t_jnode       *json_create_value(Json this, t_jnode *parent)
{
  if (((Parser)this)->read_char(this, BEGIN_ARRAY) == true)
    return (json_create_array(this, parent));
  else if (((Parser)this)->read_char(this, BEGIN_OBJECT) == true)
    return (json_create_object(this, parent));
  return (json_create_string(this, parent));
}

t_jnode       *__json_decode(Json this)
{
  Parser      _this = (Parser)this;
  t_jnode     *result;

  if (_this->read_char(this, BEGIN_ARRAY) == true)
    result = json_create_array(this, NULL);
  else if (_this->read_char(this, BEGIN_OBJECT) == true)
    result = json_create_object(this, NULL);
  else
    {
      fprintf(stderr, INVALID_FILE);
      return (NULL);
    }
  if (_this->read_eof(this) == false)
    {
      fprintf(stderr, INV_SYNTAXE);
      return (NULL);
    }
  return (result);
}
