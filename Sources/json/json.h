// ****************************************************************************
//                                                                            *
//                                   JSON H                                   *
//                                                                            *
// Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
// ****************************************************************************

#ifndef __JSON_H__
#define __JSON_H__

#include <stdlib.h>

typedef enum      e_jtype
{
  J_OBJET = 0,
  J_STRING,
  J_ARRAY
}                 t_jtype;

typedef struct    s_jnode
{
  t_jtype         type;
  void            *content;
  struct s_jnode  *parent;
  struct s_jnode  *child;
  struct s_jnode  *next;
}                 t_jnode;

typedef struct    s_json
{
  t_parser        parser;
  t_jnode         *head;
  pfct            json_get;
  t_jnode         *(*json_create_node)(struct s_json *, t_jnode *, char *);
  t_jnode         *(*json_decode)(struct s_json *);
  void            (*json_encode)(struct s_json *);
  void            (*json_free)(struct s_json *, t_jnode *);
  fct             read_string;
}                 t_json;

typedef t_json *  Json;

int               json_ctor(Json, va_list *);
int               json_dtor();

extern char *     __JSON;
extern t_module   __Json;

static int json_hinib[][4]={
  {0, '[', ']'},
  {0, '{', '}'},
  {0, '"', '"'},
};

// ------------------ special char as defined in the rfc -----------------------
#define JSON_SEP "."

#define BEGIN_ARRAY     '['     //= %x5B /            ; [    left square bracket
#define END_ARRAY       ']'     //= %x5D /            ; ]    right square bracket
#define BEGIN_OBJECT    '{'     //= %x7B /            ; {    left curly bracket
#define END_OBJECT      '}'     //= %x7D /            ; }    right curly bracket
#define NAME_SEPARATOR  ':'     //= %x3A /            ; :    colon
#define VALUE_SEPARATOR ','     //= %x2C /            ; ,    comma

#define J_TRUE          "true"  //= %x74.72.75.65     ; true
#define J_FALSE         "false" //= %x66.61.6c.73.65  ; false
#define J_NULL          "null"  //= %x6e.75.6c.6c     ; null

#define QUOTATION_MARK  '\"'    //= %x22 /            ; "    quotation mark  U+0022
#define REVERSE_SOLIDUS '\\'    //= %x5C /            ; \    reverse solidus U+005C
#define SOLIDUS         '/'     //= %x2F /            ; /    solidus         U+002F
#define BACKSPACE       'b'     //= %x62 /            ; b    backspace       U+0008
#define FORM_FEED       'f'     //= %x66 /            ; f    form feed       U+000C
#define LINE_FEED       'n'     //= %x6E /            ; n    line feed       U+000A
#define CARRIAGE_RETURN 'r'     //= %x72 /            ; r    carriage return U+000D
#define TAB             't'     //= %x74 /            ; t    tab             U+0009
#define HEXDIG          'u'     //= %x75 /  4HEXDIG   ; uXXXX                U+XXXX

#define J_DECIMAL_POINT '.'     //= %x2E /            ; .    decimal-point
#define J_MINUS         '-'     //= %x2D /            ; -    minus
#define J_PLUS          '+'     //= %x2B /            ; +    plus

// -------------------------- error messages -----------------------------------
#define UNCLOSED_OBJECT   "Json parser error : Unclosed object\n"
#define UNCLOSED_ARRAY    "Json parser error : Unclosed array\n"
#define INV_SYNTAXE       "Json parser error : Invalid syntax\n"
#define INVALID_KEY       "Json parser error : Invalid key.\n"
#define NO_NAME_SEPARATOR "Json parser error : No name separator founded\n"
#define INVALID_FILE      "A JSON text is a serialized object or array.\n"

// ------------------- json functions ---------------------------
t_jnode       *__json_decode(Json);
void          __json_encode(Json, Stream, t_jnode *, int);
void          *__json_get(Json, Array, int, t_jnode *);
void          __json_free(Json, t_jnode *);

#endif /* __JSON_H__ */
