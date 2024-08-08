NAME = philo

SRC = main.c parsing.c utils.c utils2.c simulation.c

OBJ = $(addprefix obj/, $(SRC:.c=.o))

HEADER = philo.h

FLAG = -Wall -Wextra -Werror #-g -fsanitize=thread 

all: $(NAME)

obj/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@(cc $(FLAG) -c $< -o $@)
	@printf "\rcompiling...\033[K"

$(NAME): $(OBJ)
	@(cc $(FLAG) $(OBJ) -o $(NAME))
	@printf "\r\033[K\033[33mphilo compiled\033[0m\n"

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all