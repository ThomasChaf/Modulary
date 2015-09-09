// ****************************************************************************
//                                                                            *
//                                M_MALLOC C                                  *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdlib.h>
#include <stdio.h>

void    *m_realloc(void *ptr, size_t size)
{
  void  *new_ptr = realloc(ptr, size);

  if (new_ptr == NULL)
    {
      perror("Error realloc");
      return (NULL);
    }
  return (new_ptr);
}

void    *m_malloc(size_t size)
{
  void  *ptr = malloc(size);

  if (ptr == NULL)
    {
      perror("Error malloc");
      return (NULL);
    }
  return (ptr);
}
