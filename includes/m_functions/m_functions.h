// ****************************************************************************
//                                                                            *
//                               M_FUNCTION H                                 *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#ifndef __M_FUNCTIONS_H__
#define __M_FUNCTIONS_H__

#include <sys/types.h>

typedef struct  s_hinib
{
  int           in_hinib;
  char          open;
  char          close;
}               t_hinib;

int             m_init_hinib(int hinib[][3]);
int             m_hinib(int hinib[][3], char *, int);
int             m_find(char *, char, int [][3]);
int             m_count_word(char *, char *, int [][3]);
int             m_strlen(char *, char *);
void            m_strncpy(char *, const char *, unsigned int);
void            m_strcpy(char *, char *);
char            *m_strndup(char *, unsigned int);
char            *m_strdup(char *);
char            *m_sstrdup(char *, char *);
char            *m_strcat(char *, char *);
void            *m_realloc(void *, unsigned int);
void            *m_malloc(unsigned int);
int             m_epur(char *, char *, int [][3]);
int             m_ropen(char *);
int             m_open(char *, int);
int             m_create(char *);
int             m_strcmp(char *, char *);
int             m_read(int, void *, size_t);

#endif /* __M_FUNCTIONS_H__ */
