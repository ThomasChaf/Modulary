// ****************************************************************************
//                                                                            *
//                                JSON_FREE C                                 *
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

static void   json_free_array(Json this, t_jnode *node)
{
  void        **array = (void **)node->content;
  int         i = 0;

  while (array[i] != NULL)
    {
      __json_free(this, array[i]);
      i++;
    }
  free(array);
  free(node);
}

static void   json_free_object(Json this, t_jnode *node)
{
  t_jnode     *prev;

  while (node)
    {
      prev = node;
      node = node->next;
      free(prev->content);
      __json_free(this, prev->child);
      free(prev);
    }
}

static void   json_free_string(Json this, t_jnode *node)
{
  free(node->content);
  free(node);
}

void          __json_free(Json this, t_jnode *node)
{
  if (node == NULL)
    return ;
  if (node->type == J_ARRAY)
    json_free_array(this, node);
  else if (node->type == J_OBJET)
    json_free_object(this, node);
  else if (node->type == J_STRING)
    json_free_string(this, node);
}
