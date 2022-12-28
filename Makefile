SRC		=	src/engine/cooks.cpp \
			src/engine/kitchen.cpp \
			src/engine/stock.cpp \
			src/engine.cpp \
			src/shell/shell_parser.cpp \
			src/shell/shell_reader.cpp \
			src/main.cpp \
			src/shell.cpp

CFLAGS	=	-std=gnu11 -Wall -Wextra -pthread -I include

OBJ		=	$(SRC:.cpp=.o)

INCLUDE	=	-o

LIB		=	-g -lm

NAME	=	plazza

all:	$(NAME)

$(NAME):$(OBJ)
	g++ $(OBJ) $(CFLAGS) $(INCLUDE) $(NAME) $(LIB)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re