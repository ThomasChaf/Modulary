# *****************************************************************************
#                                                                             *
#                                  MAKEFILE                                   *
#                                                                             *
#  Created by Thomas Chafiol  -  thomaschaf@gmail.com  -  20  /  09  /  2014  *
# *****************************************************************************

.PHONY: test

CC=	gcc

INCLUDES_DIR=	ModularyIncludes

SRC_DIR=	Sources

BUILT_IN=	built_in

BUILT_IN_DIR=	$(SRC_DIR)/$(BUILT_IN)

M_FUNCTIONS=	m_functions

M_FUNCTIONS_DIR=	$(SRC_DIR)/$(M_FUNCTIONS)

JSON=		json

JSON_DIR=	$(SRC_DIR)/$(JSON)

PARSER=		parser

PARSER_DIR=	$(SRC_DIR)/$(PARSER)

TEST_DIR=	test

SRC=	module.c \
	$(SRC_DIR)/liste.c \
	$(SRC_DIR)/array.c \
	$(SRC_DIR)/stream.c \
	$(SRC_DIR)/m_string.c \
	$(SRC_DIR)/buffer.c \
	$(SRC_DIR)/logger.c \
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

CFLAGS=	-g -I./$(INCLUDES_DIR) -I. -I./$(INCLUDES_DIR)/$(M_FUNCTIONS) -I./$(INCLUDES_DIR)/$(BUILT_IN) -I./$(INCLUDES_DIR)/$(JSON) -I./$(INCLUDES_DIR)/$(PARSER)

NAME=   libmod.a

all:    $(NAME) test

install:
	@cp ./modulary.h /usr/include/
	@cp -r ./$(INCLUDES_DIR) /usr/include/$(INCLUDES_DIR)
	@cp libmod.a /usr/lib
	@echo "Installation successful"
	@echo "\t* libmod.a available in : /usr/lib/libmod.a"
	@echo "\t* modulary.h available in : /usr/include/modulary.h"

uninstall:
	@rm -f /usr/lib/libmod.a
	@rm -f /usr/include/modulary.h
	@rm -rf /usr/include/$(INCLUDES_DIR)
	@echo "Uninstall successful"

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