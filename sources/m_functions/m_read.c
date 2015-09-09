// ****************************************************************************
//                                                                            *
//                                  M_READ C                                  *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>

int     m_read(int fd, void *buf, size_t nbyte)
{
  int   ret = read(fd, buf, nbyte);

  if (ret == -1)
    {
      perror("Error read");
      return (-1);
    }
  return (ret);
}
