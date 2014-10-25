# *****************************************************************************
#                                                                             *
#                                  MAKEFILE                                   *
#                                                                             *
#  Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
# *****************************************************************************

.PHONY: test

CC=	gcc

SRC_DIR=	Sources

BUILT_IN_DIR=	$(SRC_DIR)/built_in

M_FUNCTIONS_DIR=	$(SRC_DIR)/m_functions

JSON_DIR=	$(SRC_DIR)/json

PARSER_DIR=	$(SRC_DIR)/parser

TEST_DIR=	test

SRC=	module.c \
	$(SRC_DIR)/liste.c \
	$(SRC_DIR)/array.c \
	$(SRC_DIR)/stream.c \
	$(SRC_DIR)/m_string.c \
	$(SRC_DIR)/buffer.c \
	$(BUILT_IN_DIR)/str.c \
	$(BUILT_IN_DIR)/iter.c \
	$(BUILT_IN_DIR)/next.c \
	$(BUILT_IN_DIR)/sum.c \
	$(BUILT_IN_DIR)/len.c \
	$(BUILT_IN_DIR)/push.c \
	$(BUILT_IN_DIR)/get.c \
	$(BUILT_IN_DIR)/type.c \
	$(M_FUNCTIONS_DIR)/m_find.c \
	$(M_FUNCTIONS_DIR)/m_strcat.c \
	$(M_FUNCTIONS_DIR)/m_strcpy.c \
	$(M_FUNCTIONS_DIR)/m_strdup.c \
	$(M_FUNCTIONS_DIR)/m_strlen.c \
	$(M_FUNCTIONS_DIR)/m_malloc.c \
	$(M_FUNCTIONS_DIR)/m_epur.c \
	$(M_FUNCTIONS_DIR)/m_open.c \
	$(M_FUNCTIONS_DIR)/m_strcmp.c \
	$(M_FUNCTIONS_DIR)/m_read.c \
	$(JSON_DIR)/json.c \
	$(JSON_DIR)/json_decode.c \
	$(JSON_DIR)/json_encode.c \
	$(JSON_DIR)/json_get.c \
	$(JSON_DIR)/json_free.c \
	$(PARSER_DIR)/parser.c

OBJ=	$(SRC:.c=.o)

CFLAGS=	-g -I./Includes -I. -I./$(M_FUNCTIONS_DIR) -I./$(BUILT_IN_DIR) -I./$(JSON_DIR) -I./$(PARSER_DIR)

NAME=   libmod.a

all:    $(NAME) test

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

test:
	make -C test

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
