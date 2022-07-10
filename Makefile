FT_NAME	=	ft_containers

FOLDER	=	./

SRC_LIST	=	ft_main.cpp

HDRS_LIST	=	vector.hpp map.hpp stack.hpp set.hpp pair.hpp

SRC	=	$(addprefix $(FOLDER), $(SRC_LIST))

HDRS	=	$(addprefix $(FOLDER), $(HDRS_LIST))

OBJ	=	$(patsubst, %.cpp, %.o, $(SRC))

CC	=	c++

CFLAGS	=	-Wall -Wextra -Werror -std=c++98 -pedantic-errors

.PHONY:	all clean fclean re

all:	$(FT_NAME)

$(FT_NAME):	Makefile $(OBJ) $(HDRS)
			$(CC) $(CFLAGS) $(HDRS) $(OBJ) -o $(FT_NAME)

%.o:	%.cpp $(HDRS)
		$(CC) $(CFLAGS) $(HDRS) -o $@ -c $<

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME_VEC) $(NAME_STACK) $(NAME_MAP) $(NAME_SET)

re:	fclean all