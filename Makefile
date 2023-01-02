NAME = pipex
LIBFT = libft/libft.a
LIBPIPEX = libpipex.a
LIBGNL = 42-get-next-line/libgnl.a
LIBBONUS = libpipexbonus.a
SRCS = srcs/validate.c \
	   srcs/pipex_inits.c \
	   srcs/path_manipulate.c \
	   srcs/treat_quotes.c \
	   srcs/pipex_mandatory.c \
	   srcs/err_handler.c
BONUS_SRCS = srcs_bonus/pipex_bonus.c \
			 srcs_bonus/validate_bonus.c \
			 srcs_bonus/err_handler_bonus.c \
			 srcs_bonus/treat_quotes_bonus.c \
			 srcs_bonus/pipex_inits_bonus.c \
			 srcs_bonus/run_cmds_bonus.c \
			 srcs_bonus/path_manipulate_bonus.c

LIBFT_PATH = ./libft/
GNL_PATH = ./42-get-next-line/
LIBS = -lft
LIBS_BONUS = -lft -lgnl
FLAGS = -Wall -Wextra -Werror -g3
OBJS = $(SRCS:%.c=%.o)
BONUS_OBJS = $(BONUS_SRCS:%.c=%.o)

all : | libft

libft : 
	make -C ./libft
	make $(NAME)

gnl :
	make -C ./42-get-next-line/

$(NAME) : $(LIBPIPEX) $(LIBFT)
	cc $(FLAGS) $(LIBPIPEX) -o $(NAME) -L./libft/ $(LIBS) 

$(LIBFT):
	make -C $(LIBFT_PATH) --no-print-directory

$(LIBPIPEX): $(OBJS)
	ar rcs $(LIBPIPEX) $(OBJS)

%.o:%.c
	@cc $(FLAGS) -I ./includes -c $< -o $@

bonus: libft gnl $(LIBBONUS)

$(LIBBONUS): $(BONUS_OBJS) $(LIBFT) $(LIBGNL)
	ar rcs $(LIBBONUS) $(BONUS_OBJS)
	cc $(FLAGS) $(LIBBONUS) -o $(NAME) -L./libft/ -L./42-get-next-line/ $(LIBS_BONUS) 

clean :
	rm -f $(OBJS)
	rm -f $(BONUS_OBJS)
	@make clean -C $(LIBFT_PATH) --no-print-directory

fclean : clean
	rm -f $(NAME) $(LIBPIPEX)
	@make fclean -C $(LIBFT_PATH) --no-print-directory

re : fclean all

.PHONY : all clean fclean re libft gnl
