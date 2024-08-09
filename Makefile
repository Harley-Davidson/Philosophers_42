SRC     =       philo/main.c           \
				philo/table.c          \
				philo/philosopher.c    \
				philo/simulation.c     \
				philo/setters_getters.c\
				philo/error_handlers.c \
				philo/utils.c

SRC_bonus =     philo_bonus/main.c      \
				philo_bonus/table.c    \
				philo_bonus/philosopher.c\
				philo_bonus/simulation.c\
				philo_bonus/setters_getters.c\
				philo_bonus/error_handlers.c\
				philo_bonus/utils.c

OBJS    = $(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.c=.o)))
OBJS_bonus = $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_bonus:.c=.o)))

BUILD_DIR = build
BIN_DIR = bin

NAME    = $(BIN_DIR)/philo
NAME_bonus = $(BIN_DIR)/philo_bonus

AR      = ar rcs

RM      = rm -f

LIB     = ranlib

GCC     = gcc -g -lpthread

CFLAGS  = -Wall -Wextra -Werror

all: $(BIN_DIR) $(BUILD_DIR) $(NAME)

$(NAME): $(OBJS)
		$(GCC) $(CFLAGS) -o $(NAME) $(OBJS)

bonus: $(BIN_DIR) $(BUILD_DIR) $(OBJS_bonus)
		$(GCC) $(CFLAGS) -o $(NAME_bonus) $(OBJS_bonus)

$(BUILD_DIR)/%.o: philo/%.c
		$(GCC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: philo_bonus/%.c
		$(GCC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(BUILD_DIR):
		mkdir -p $@

clean:
		rm -f $(OBJS) $(OBJS_bonus)
		rm -rf $(BUILD_DIR)

fclean: clean
		rm -f $(NAME) $(NAME_bonus)
		rm -rf $(BIN_DIR)

re: fclean all

.PHONY: all bonus clean fclean re
