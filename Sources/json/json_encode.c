// ****************************************************************************
//                                                                            *
//                               JSON_ENCODE C                                *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "stream.h"
#include "buffer.h"
#include "array.h"
#include "parser.h"
#include "json.h"

static void     indentation(Stream stream, int n, t_jnode *node)
{
  int           j = 0;

  if (node)
    stream->cout(stream, "\n");
  while (j++ < n)
    stream->cout(stream, "\t");
}

static void     encode_objet(Json this, Stream stream, t_jnode *node, int i)
{
  t_jnode       *tmp = node;

  stream->cout(stream, "{\n");
  while (tmp != NULL)
    {
      if (tmp != node)
        stream->cout(stream, ",\n");
      indentation(stream, i + 1, NULL);
      if (tmp->content == NULL && tmp->child == NULL)
        break ;
      stream->cout(stream, "%s : ", tmp->content);
      __json_encode(this, stream, tmp->child, i + 2);
      tmp = tmp->next;
    }
  indentation(stream, i, node);
  stream->cout(stream, "}");
}

static void     encode_array(Json this, Stream stream, t_jnode *node, int i)
{
  int           j = 0;

  stream->cout(stream, "[\n");
  if (node->content == NULL)
    return ;
  void **tab = ((void **)node->content);
  while (tab[j] != NULL)
    {
      if (j != 0)
        stream->cout(stream, ",\n");
      __json_encode(this, stream, tab[j++], i + 1);
    }
  indentation(stream, i, node);
  stream->cout(stream, "]");
}

void            __json_encode(Json this, Stream stream, t_jnode *node, int i)
{
  if (node == NULL)
    {
      stream->cout(stream, "NULL\n");
      return ;
    }
  if (node->type == J_OBJET)
    {
      indentation(stream, i, node);
      encode_objet(this, stream, node, i);
    }
  else if (node->type == J_ARRAY)
  {
    indentation(stream, i, node);
    encode_array(this, stream, node, i);
  }
  else if (node->type == J_STRING)
    {
      indentation(stream, i, NULL);
      stream->cout(stream, "\"%s\"", (char *)node->content);
    }
  else
    fprintf(stderr, "Error, Unkonwn node type %d\n", node->type);
}
