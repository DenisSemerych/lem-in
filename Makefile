NAME = lem-in

FLAGS = -Wall -Wextra -Werror

SRC = algorithm.c lists_creation.c memory_cleaning.c queue_functions.c extra.c main.c moving_ants.c validation.c

OBJ = $(SRC:%.c=%.o)

INCL = includes/lem-in.h includes/printf.h includes/libft.h

all:
	@echo "Making libft"
	@make -C libft/
	@echo "Making lem-in"
	@gcc $(FLAGS) $(SRC) libft/libftprintf.a -o $(NAME)
	@echo "Done!"

clean:
	@make clean -C libft
	@rm -rf $(OBJ)
fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all
