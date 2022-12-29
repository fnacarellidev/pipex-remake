NAME = pipex
LIBPIPEX = libpipex.a
SRCS = srcs/validate.c \
	   srcs/pipex_inits.c \
	   srcs/path_manipulate.c \
	   srcs/get_names_and_params.c \
	   srcs/treat_quotes.c \
	   srcs/pipex_mandatory.c \
	   srcs/err_handler.c
LIBFT_PATH = ./libft
PATH_LIBS = -L$(LIBFT_PATH)
LIBS = -lft
FLAGS = -Wall -Wextra -Werror -g3
OBJS = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME) : $(LIBPIPEX)
	@make -C $(LIBFT_PATH) --no-print-directory
	cc $(FLAGS) $(OBJS) -o $(NAME) $(PATH_LIBS) $(LIBS)

$(LIBPIPEX): $(OBJS)
	ar rcs $(LIBPIPEX) $(OBJS)

%.o:%.c
	@cc $(FLAGS) -I ./includes -c $< -o $@

clean :
	rm -f $(OBJS)
	@make clean -C $(LIBFT_PATH) --no-print-directory

fclean : clean
	rm -f $(NAME) $(LIBPIPEX)
	@make fclean -C $(LIBFT_PATH) --no-print-directory

re : fclean all

.PHONY : all clean fclean re
