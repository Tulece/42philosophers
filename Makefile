NAME		=	philo
NAME_BONUS	=	philo_bonus
CC			=	cc
FLAGS		=	-g -Wall -Werror -Werror

SRC			=	$(wildcard src/*.c)
OBJ			=	$(patsubst %.c,%.o,$(SRC))
SRC_BONUS	=	$(wildcard src_bonus/*.c)
OBJ_BONUS	=	$(patsubst %.c,%.o,$(SRC_BONUS))
RM 			=	rm -f

.SUFFIXES: .c .o

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -I includes/

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ -I includes/


all: $(NAME)

bonus: $(NAME_BONUS)
$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(FLAGS) $(OBJ_BONUS) -o $(NAME_BONUS) -I includes/

clean:
	@rm -f $(OBJ)
	@rm -f $(OBJ_BONUS)
	@echo "Done\n"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@echo "Done\n"

re: fclean all

.PHONY: all clean fclean re
