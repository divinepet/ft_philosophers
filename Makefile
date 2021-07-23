NAME = philo
INCLUDE = lib.h
SRCS = 	main.c \
		cycle.c \
		utilities.c \
		\
		lib/ft_atoi.c \
		lib/ft_isdigit.c \
		lib/ft_itoa.c \
		lib/ft_strjoin.c \
		lib/ft_strlen.c
		
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
		@clang  $(SRCS) -o $(NAME)

%.o:%.c
		@clang -c -g $< -o $@

clean:
		@rm -rf $(OBJS)

fclean: clean
		@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
