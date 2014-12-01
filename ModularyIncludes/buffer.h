// ****************************************************************************
//                                                                            *
//                                 BUFFER H                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// *****************************************************************************

#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "modulaire.h"
#include "m_string.h"

typedef struct      s_buffer
{
  t_string          parent;
  fct               bufferized;
  fct               concat;
}                   t_buffer;

typedef t_buffer *  Buffer;

int                 buffer_ctor(Buffer);
int                 buffer_dtor();

extern char         *__BUFFER;
extern t_module     __Buffer;

#endif /* __BUFFER_H__ */
