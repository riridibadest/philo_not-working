CC := cc

CFLAGS := -Wall -Wextra -Werror -g
IFLAGS := -I.


NAME := philo

SRC_FILES := feast.c help.c help2.c main.c make_table.c routine.c
OBJ_FILES := $(SRC_FILES:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)

debug: $(OBJ_FILES)
	$(CC) -g $(CFLAGS) $(OBJ_FILES) -o $(NAME)_debug

%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf *.o

fclean: clean
	rm -f $(NAME) $(NAME)_debug

re: fclean all

.PHONY: all clean fclean re
