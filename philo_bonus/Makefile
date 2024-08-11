NAME = philo_bonus

SRC_BONUS = main_bonus.c parsing_bonus.c simulation_bonus.c utils_bonus.c utils2_bonus.c

OBJ_BONUS = $(addprefix obj_bonus/, $(SRC_BONUS:.c=.o))

HEADER = philo_bonus.h

FLAG = -Wall -Wextra -Werror

all: $(NAME)

obj_bonus/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@(cc $(FLAG) -c $< -o $@)
	@printf "\rcompiling...\033[K"

$(NAME): $(OBJ_BONUS)
	@(cc $(FLAG) $(OBJ_BONUS) -o $(NAME))
	@printf "\r\033[K\033[33mphilo compiled\033[0m\n"

clean:
	rm -rf obj_bonus

fclean: clean
	rm -rf $(NAME)

re: fclean all