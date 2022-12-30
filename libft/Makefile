NAME = libft.a

CFLAGS = -Wall -Wextra -Werror
CFILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		 ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memmove.c \
		 ft_memcpy.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
		 ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
		 ft_strnstr.c ft_calloc.c ft_strdup.c ft_atoi.c ft_putchar_fd.c \
		 ft_putstr_fd.c ft_putendl_fd.c ft_substr.c ft_strjoin.c ft_striteri.c \
		 ft_strmapi.c ft_itoa.c ft_putnbr_fd.c  ft_strtrim.c ft_split.c \
		 ft_putstr.c ft_putchar.c ft_putnbr_base.c ft_printf_utils.c \
		 ft_printf.c ft_count_matrix.c ft_free_matrix.c \
		 ft_free_spatial_matrix.c ft_free_matrix_size_n.c ft_strcmp.c

OBJS = ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o \
		 ft_isprint.o ft_strlen.o ft_memset.o ft_bzero.o ft_memmove.o \
		 ft_memcpy.o ft_strlcpy.o ft_strlcat.o ft_toupper.o ft_tolower.o \
		 ft_strchr.o ft_strrchr.o ft_strncmp.o ft_memchr.o ft_memcmp.o \
		 ft_strnstr.o ft_calloc.o ft_strdup.o ft_atoi.o ft_putchar_fd.o \
		 ft_putstr_fd.o ft_putendl_fd.o ft_substr.o ft_strjoin.o ft_striteri.o \
		 ft_strmapi.o ft_itoa.o ft_putnbr_fd.o ft_strtrim.o ft_split.o \
		 ft_putstr.o ft_putchar.o ft_putnbr_base.o ft_printf.o ft_printf_utils.o \
		 ft_count_matrix.o ft_free_matrix.o ft_free_spatial_matrix.o \
		 ft_free_matrix_size_n.o ft_strcmp.o
	   
BONUS_FILES = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
			  ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

BONUS_OBJ = ft_lstnew.o ft_lstadd_front.o ft_lstsize.o ft_lstlast.o ft_lstadd_back.o \
			ft_lstdelone.o ft_lstclear.o ft_lstiter.o ft_lstmap.o


all : $(NAME)

$(NAME) : $(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(OBJS) : $(CFILES)
	@cc $(CFLAGS) -I ./ -c $(CFILES)

$(BONUS_OBJ) :
	@cc $(CFLAGS) -I ./ -c $(BONUS_FILES)
	@ar rcs $(NAME) $(BONUS_OBJ)

bonus : $(BONUS_OBJ)

fclean : clean
	@rm -f $(NAME)

clean :
	@rm -f $(OBJS) $(BONUS_OBJ)

re : fclean all
