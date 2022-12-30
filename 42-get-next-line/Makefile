NAME = libgnl.a
SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:%.c=%.o)
FLAGS = -Wall -Wextra -Werror -g3
LIBFT_PATH = ../libft/
LIBS = -lft

all : $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o:%.c
	cc $(FLAGS) -I ../libft -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
