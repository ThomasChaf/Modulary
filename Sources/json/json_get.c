// ****************************************************************************
//                                                                            *
//                                 JSON_GET C                                 *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "m_functions.h"
#include "stream.h"
#include "buffer.h"
#include "parser.h"
#include "array.h"
#include "json.h"
#include "built_in.h"

static void   *get_objet(Json this, Array needles, int index, t_jnode *node)
{
  while (node)
    {
      if (m_strcmp(node->content, get(needles, index)) == 0)
        return (__json_get(this, needles, index + 1, node->child));
      node = node->next;
    }
  return (NULL);
}

static void   *get_array(Json this, Array needles, int index, t_jnode *node)
{
  void        **tab = ((void **)node->content);
  int         i = 0;
  int         j = INT(get(needles, index));

  while (j != 0 && tab[i] != NULL)
    {
      if (i == j)
        return (__json_get(this, needles, index + 1, tab[i]));
      i++;
    }
  return (NULL);
}

static void   *get_string(Json this, Array needles, int index, t_jnode *node)
{
  if (get(needles, index) == NULL)
    return (node->content);
  return (NULL);
}

void          *__json_get(Json this, Array needles, int index, t_jnode *node)
{
  if (node == NULL)
    return (NULL);
  if (node->type == J_STRING)
    {
      return (get_string(this, needles, index, node));
    }
  else if (node->type == J_OBJET)
    {
      return (get_objet(this, needles, index, node));
    }
  else if (node->type == J_ARRAY)
    {
      return (get_array(this, needles, index, node));
    }
  return (NULL);
}
