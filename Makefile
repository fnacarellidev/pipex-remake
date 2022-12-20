NAME = pipex
LIBPIPEX = libpipex.a
SRCS = validate.c pipex_inits.c path_manipulate.c \
	   get_names_and_params.c
OBJS = $(patsubst %.c, %.o, $(SRCS))
LIBFT_PATH = ./libft
PATH_LIBS = -L$(LIBFT_PATH)
LIBS = -lft
FLAGS = -Wall -Wextra -Werror -g3

all : $(NAME)

$(NAME) : $(LIBPIPEX)
	@make -C $(LIBFT_PATH) --no-print-directory
	cc $(FLAGS) $(OBJS) -o $(NAME) main.c $(PATH_LIBS) $(LIBS)
	make cleanthis

$(LIBPIPEX): $(OBJS)
	ar rcs $(LIBPIPEX) $(OBJS)

$(OBJS) : $(SRCS)
	@cc $(FLAGS) -I ./includes -c $(SRCS)

clean : cleanthis
	@make clean -C $(LIBFT_PATH)

cleanthis :
	rm -f $(OBJS) $(LIBPIPEX)

fclean : clean
	rm -f $(NAME)
	@make clean -C $(LIBFT_PATH)

debug :
	gcc -g3 -O1 get_names_and_params.c path_manipulate.c pipex_inits.c validate.c libft/*.c main.c

re : fclean all
	make cleanthis

.PHONY : all clean fclean re
