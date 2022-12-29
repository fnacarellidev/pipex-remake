NAME = pipex
LIBPIPEX = libpipex.a
SRCS = validate.c pipex_inits.c path_manipulate.c \
	   get_names_and_params.c treat_quotes.c pipex_mandatory.c err_handler.c
OBJS = $(patsubst %.c, %.o, $(SRCS))
LIBFT_PATH = ./libft
PATH_LIBS = -L$(LIBFT_PATH)
LIBS = -lft
FLAGS = -Wall -Wextra -Werror -g3

all : $(NAME)

$(NAME) : $(LIBPIPEX)
	@make -C $(LIBFT_PATH) --no-print-directory
	cc $(FLAGS) $(OBJS) -o $(NAME) $(PATH_LIBS) $(LIBS)

$(LIBPIPEX): $(OBJS)
	ar rcs $(LIBPIPEX) $(OBJS)

$(OBJS) : $(SRCS)
	@cc $(FLAGS) -I ./includes -c $(SRCS)

clean :
	rm -f $(OBJS)
	@make clean -C $(LIBFT_PATH) --no-print-directory

fclean : clean
	rm -f $(NAME) $(LIBPIPEX)
	@make fclean -C $(LIBFT_PATH) --no-print-directory

re : fclean all

.PHONY : all clean fclean re
