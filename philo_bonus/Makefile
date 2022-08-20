NAME		= 	philo_bonus
HDR			= 	philo_bonus.h
SRC			= 	main.c utilities.c inits.c routine.c
OBJ			=	$(patsubst %.c, %.o,$(SRC))
FLAGS		= 	-Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ) $(HDR)
	gcc $(FLAGS) $(OBJ) -I $(HDR) -o $@

%.o : %.c $(HDR)
	gcc $(FLAGS) -I $(HDR) -c $< -o $@

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
