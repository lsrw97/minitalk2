DIRLIB		= ./ft_printf/libft/
DIRLIB2		= ./ft_printf/


SRCS	=	client.c\
			server.c

OBJ	= ${SRCS:.c=.o}

LIBFT   = ./ft_printf/libft/libft.a

PRINTF   = ./ft_printf/printlibft.a

NAME	= minitalk.a

CC		= gcc

AR		= ar rcs

RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror

NAMELFT		= libft.a

all:		${NAME}

$(NAME):	$(OBJ) $(LIBFT) $(PRINTF)
				ar rcs $(NAME) $(OBJ)

$(LIBFT):
	make -C ./ft_printf/libft
	cp ./ft_printf/libft/libft.a $(NAME)

$(PRINTF): $(LIBFT)
	make -C ./ft_printf/
	cp ./ft_printf/libftprintf.a $(NAME)

clean:
	make clean -C ./ft_printf/libft
	make clean -C ./ft_printf
	$(RM) $(OBJ) $(BOBJ)

fclean: clean
	make fclean -C ./ft_printf/libft
	make fclean -C ./ft_printf
	$(RM) $(NAME)

re:			fclean all
				cd ${DIRLIB} && ${MAKE} clean
				cd ${DIRLIB2} && ${MAKE} clean

.PHONY:		all clean fclean re
