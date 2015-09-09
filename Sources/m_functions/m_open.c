// ****************************************************************************
//                                                                            *
//                                 M_OPEN C                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <stdio.h>
#include <fcntl.h>

int   m_open(char *file, int flags)
{
  int fd = open(file, flags);

  if (fd == -1)
    {
      perror("Error");
      return (-1);
    }
  return (fd);
}

int  m_ropen(char *file)
{
    return m_open(file, O_RDONLY);
}

int   m_create(char *file)
{
  return m_open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
}
