#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

#include "modulary.h"

void build_in()
{
  void *objet;

  objet = new(__Array, 1);
  printf("%d # test type array\n", strcmp(type(objet), "array") == 0); delete(objet);
  objet = new(__Buffer);
  printf("%d # test type buffer\n", strcmp(type(objet), "buffer") == 0); delete(objet);
  objet = new(__Liste);
  printf("%d # test type stream\n", strcmp(type(objet), "liste") == 0); delete(objet);
  objet = new(__String, "toto");
  printf("%d # test type string\n", strcmp(type(objet), "string") == 0); delete(objet);
  objet = new(__Stream, 1);
  printf("%d # test type stream\n", strcmp(type(objet), "stream") == 0); delete(objet);
}

void     m_functions()
{
  char   *ptr;
  char   dest[10];

  ptr = m_malloc(3);
  printf("%d # test m_malloc: ok\n", (ptr != NULL)); free(ptr);
  printf("%d # test m_find: ok\n", m_find("azertyuiop", 'p', NULL) == 9);
  printf("%d # test m_find: -1\n", m_find("azertyuiop", 'm', NULL) == -1);
  printf("%d # test m_find: NULL\n", m_find(NULL, 'm', NULL) == -1);
  printf("%d # test m_count_word: ok\n", m_count_word("voici cinq jolies petits mots", " ", NULL) == 5);
  printf("%d # test m_count_word: NULL\n", m_count_word(NULL, " ", NULL) == -1);
  int hinib[][3]={
    {0, '(', ')'},
    0
  };
  printf("%d # test m_count_word: hinib\n", m_count_word("voici cinq ------------jolies -((-( --tres)) beau )- petits -- mots ", " -", hinib) == 6);
  ptr = m_strcat("toto", "papa");
  printf("%d # test m_strcat: ok\n", strcmp(ptr, "totopapa") == 0); free(ptr);
  ptr = m_strcat("toto", NULL);
  printf("%d # test m_strcat: only right\n", strcmp(ptr, "toto") == 0); free(ptr);
  ptr = m_strcat(NULL, "papa");
  printf("%d # test m_strcat: only left\n", strcmp(ptr, "papa") == 0); free(ptr);
  ptr = m_strcat(NULL, NULL);
  printf("%d # test m_strcat: NULL & NULL\n", strcmp(ptr, "") == 0); free(ptr);
  memset(dest, 'a', 10);
  m_strcpy(dest, "toto");
  printf("%d # test m_strcpy: ok\n", (strcmp(dest, "toto") == 0));
  memset(dest, 'a', 10);
  m_strcpy(dest, NULL);
  printf("%d # test m_strcpy: fail\n", (strncmp(dest, "aaaaaaaaaa", 10) == 0));
  memset(dest, 'a', 10);
  m_strncpy(dest, "toto", 2);
  printf("%d # test m_strncpy: ok\n", (strcmp(dest, "to") == 0));
  ptr = m_strdup("toto");
  printf("%d # test m_strdup: ok\n", strcmp(ptr, "toto") == 0); free(ptr);
  printf("%d # test m_strdup: NULL\n", m_strdup(NULL) ==  NULL);
  printf("%d # test m_strlen: ok\n", m_strlen("toto", "") == 4);
  printf("%d # test m_strlen: sep\n", m_strlen("totoZ", "Z") == 4);
  printf("%d # test m_strlen: NULL\n", m_strlen(NULL, "") == 0);
}

void    liste_test()
{
  Liste  liste;
  Iter   it;
  Objet  first;

  liste = new(__Liste);
  printf("%d # test Liste: push_back\n", (push_back(liste, "premier") == true));
  printf("%d # test Liste: push\n", (push(liste, "premier") == true));
  printf("%d # test Liste: push_front\n", (push_front(liste, "premier") == true));
  it = iter(liste);
  printf("%d # test Liste: iter\n", (it != NULL));
  while (it)
    {
      printf("%d # test Liste: next\n", (strcmp(it->content, "premier") == 0));
      it = next(it);
    }
  free(it);
  first = pop(liste);
  printf("%d # test Liste: pop\n", (strcmp(first, "premier") == 0));
  printf("%d # test Liste: len after pop\n", (len(liste) == 2));

  Liste  liste2;
  liste2 = new(__Liste);
  printf("%d # test Liste: push_front\n", (push_front(liste2, "six") == true));
  printf("%d # test Liste: push_front\n", (push_front(liste2, "cinq") == true));
  printf("%d # test Liste: push_front\n", (push_front(liste2, "quatre") == true));

  Liste  sumliste;
  sumliste = sum(liste, liste2);
  printf("%d # test Liste: len sumliste\n", (len(sumliste) == 5));
  Liste sumliste2 = sum(sumliste, NULL);
  delete(liste);
  delete(liste2);
  delete(sumliste);
  delete(sumliste2);
}

void    array_test()
{
  Array  array;
  Iter   it;
  Objet  first;

  array = new(__Array, 3);
  printf("%d # test Array: push 1\n", (push(array, "premier") == true));
  printf("%d # test Array: push 2\n", (push(array, "premier") == true));
  printf("%d # test Array: push 3\n", (push(array, "premier") == true));
  printf("%d # test Array: push impossible\n", (push(array, "quatrieme") == false));
  it = iter(array);
  printf("%d # test Array: iter\n", (it != NULL));
  while (it)
    {
      printf("%d # test Array: next\n", (strcmp(it->content, "premier") == 0));
      it = next(it);
    }
  first = get(array, 0);
  printf("%d # test Array: get\n", (strcmp(first, "premier") == 0));
  printf("%d # test Array: get impossible\n", (get(array, 42) == NULL));
  printf("%d # test Array: len\n", (len(array) == 3));

  Array  array2;
  array2 = new(__Array, 3);
  push(array2, "quatre");
  push(array2, "cinq");
  push(array2, "six");

  Array  sumarray;
  sumarray = sum(array, array2);
  printf("%d # test Array: len sum\n", (len(sumarray) == 6));
  first = get(sumarray, 5);
  printf("%d # test Array: get %p\n", (strcmp(first, "six") == 0), first);
  str(NULL);
  Array sumarray2 = sum(sumarray, NULL);
  delete(array);
  delete(array2);
  delete(sumarray);
  delete(sumarray2);
}

void    string_test()
{
  String  string;
  String  string2;
  Array   array;
  Iter   it;
  Objet  first;

  string = new(__String, "1");
  string2 = new(__String, "1");

  String  sumstring;

  sumstring = sum(string, string2);
  printf("%d # test String: len\n", (len(sumstring) == 2));
  str(NULL);
  String sumstring2 = sum(string, NULL);
  it = iter(string2);
  printf("%d # test String: iter\n", (it != NULL));
  char c;
  while (it)
    {
      c = *((char *)(it->content));
      printf("%d # test String: iter & next\n", (c == '1'));
      it = next(it);
    }
  delete(string);
  string = new(__String, "maman fait des gateaux");
  array = string->split(string, " ", NULL);
  printf("%d # test String: split\n", (c == '1'));
  printf("%d # test Array & String: get & split\n", (strcmp(get(array, 0), "maman") == 0));
  printf("%d # test Array & String: get & split\n", (strcmp(get(array, 3), "gateaux") == 0));
  printf("%d # test Array & String: get & split\n", (get(array, 4) == NULL));
  printf("%d # test String: get\n", (strcmp(str(string2), "1") == 0));
  printf("%d # test String: at simple\n", (*(char *)get(string2, 0) == '1'));
  printf("%d # test String: at excessif\n", get(string2, 42) == NULL);
  string2->set(string2, 0, '4');
  printf("%d # test String: set simple\n", (*(char *)get(string2, 0) == '4'));
  printf("%d # test String: set impossible\n", (string2->set(string2, -30, 'e') == false));
  delete(string);
  delete(string2);
  delete(sumstring);
  delete(sumstring2);
  delete(array);
}

void    stream_test()
{
  Stream  stream;
  Buffer  buff = new(__Buffer);
  int     in = open("./input_file.txt", O_RDONLY);

  stream = new(__Stream, in);
  stream->read(stream, buff);
  printf("%d # test Stream & String: cin & get\n", (strcmp(str(buff), "premier") == 0));
  buff->bufferized(buff, "-second");
  printf("%d # test Buffer: bufferized & get %s\n", (strcmp(str(buff), "premier-second") == 0), (char *)get(buff, 42));
  delete(stream);
  delete(buff);
}

void      parser_test()
{
  Stream  stream;
  Parser  parser;
  int     in = open("./input_file.txt", O_RDONLY);

  if (in == -1)
    perror("");
  stream = new(__Stream, in);
  parser = new(__Parser, stream);
  printf("%d # test Parser: read char\n", (parser->read_char(parser, 'p')) > 0);
  printf("%d # test Parser: read range\n", (parser->read_range(parser, 'a', 'z')) > 0);
  printf("%d # test Parser: read text\n", (parser->read_text(parser, "emier")) > 0);
  printf("%d # test Parser: read bad text\n", (parser->read_text(parser, "remier")) == 0);
  delete(stream);
  delete(parser);
}

void      json_test()
{
  DIR     *rep = opendir("./json_files/");
  Stream  stream;
  Json    parser;
  void    *ptr;

  if (rep == NULL)
    perror("");
  struct dirent* ent = NULL;
  while ((ent = readdir(rep)) != NULL)
  {
    printf("-- test sur %s\n", ent->d_name);
    ptr = m_strcat("./json_files/", ent->d_name);
    if (strncmp("fail", ent->d_name, 4) == 0)
    {
      stream = new(__Stream, open(ptr, O_RDONLY));
      parser = new(__Json, stream);
      printf("%d # test Parser json %s\n", parser->json_decode(parser) == NULL, ent->d_name);
      delete(stream);
      delete(parser);
    }
    else if (strncmp("pass", ent->d_name, 4) == 0)
    {
      stream = new(__Stream, open(ptr, O_RDONLY));
      parser = new(__Json, stream);
      printf("%d # test Parser json %s\n", parser->json_decode(parser) != NULL, ent->d_name);
      delete(stream);
      delete(parser);
    }
    free(ptr);
  }
  stream = new(__Stream, open("./json_files/pass1.json", O_RDONLY));
  parser = new(__Json, stream);
  printf("--before\n");
  parser->json_decode(parser);
  delete(stream);
  stream = new(__Stream, 1);
  printf("%d # test Parser set\n", ((Parser)parser)->set(parser, stream));
  printf("#####\n");
  parser->json_encode(parser);
  printf("#####\n");
  ptr = new(__String, "8.integer");
  printf("%d # test Json get\n", m_strcmp(parser->json_get(parser, ptr, NULL), "1234567890") == 0); delete(ptr);
  ptr = new(__String, "8/integer");
  printf("%d # test Json get fail\n", m_strcmp(parser->json_get(parser, ptr, NULL), "1234567890") != 0); delete(ptr);
  ptr = new(__String, NULL);
  printf("%d # test Json get fail\n", m_strcmp(parser->json_get(parser, ptr, NULL), "1234567890") != 0); delete(ptr);
  ptr = new(__String, "");
  printf("%d # test Json get fail\n", m_strcmp(parser->json_get(parser, ptr, NULL), "1234567890") != 0); delete(ptr);
  ptr = new(__String, "toto");
  printf("%d # test Json get fail\n", m_strcmp(parser->json_get(parser, ptr, NULL), "1234567890") != 0); delete(ptr);
  closedir(rep);
  delete(stream);
  printf("-----------------\n");
  delete(parser);
}

void     logger_test()
{
  LOG_INFO("1 # Je log une info simple\n");
  LOG_INFO("1 # Je log une info avec un argument %s\n", "[argument]");
  LOG_ERROR("1 # Je log une erreur simple\n");
  LOG_ERROR("1 # Je log une erreur avec un argument %s\n", "[argument]");
}

int      main()
{
  build_in();
  m_functions();
  liste_test();
  array_test();
  string_test();
  stream_test();
  parser_test();
  json_test();
  logger_test();
  return (0);
}
