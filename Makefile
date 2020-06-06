##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

SRC	=	tests/src/main.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-W -Wall -Wextra -I include --coverage

NAME	=	tests_run

all:	$(NAME)

debug:	CFLAGS += -g
debug:	all

debugre:	CFLAGS += -g
debugre:	re

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

tests_run:
	g++ $(SRC_TEST) -o tests_run -lgtest -lgtest_main -lpthread --coverage
	./tests_run

re:	fclean all
