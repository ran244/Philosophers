NAME = philo
SRCS = src/checking.c src/initializing.c src/main.c src/creating.c src/routine.c src/utils.c
CFLAGS = -Wall -Werror -Wextra -g
OBJ=$(SRCS:src/%.c=obj/%.o)

all : $(NAME)
$(NAME) : $(OBJ)
	cc $^ $(CFLAGS) -o $@

obj/%.o : src/%.c
	mkdir -p obj
	cc $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)
	rm -rf obj

fclean : clean
	rm -f $(NAME)
	-
re : fclean all

.PHONY : all clean fclean re
