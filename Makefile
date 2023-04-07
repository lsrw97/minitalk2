DIRLIB		= ./ft_printf/libft/
DIRLIB2		= ./ft_printf/


SRCS	=	client.c\
			server.c

LIBFT   = ./ft_printf/libft/libft.a

PRINTF   = ./ft_printf/printlibft.a

CC		= gcc

OBJS		= client server

AR		= ar rcs

RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror

NAMELFT	= libft.a

all:		${PRINTF} $(LIBFT) server

$(LIBFT):
	make -C ./ft_printf/libft

$(PRINTF): $(LIBFT)
	make -C ./ft_printf/

server:		${PRINTF} $(LIBFT) client.c server.c
	gcc server.c ./ft_printf/printlibft.a ft_printf/libft/libft.a -o server -Werror -Wall -Wextra
	gcc client.c ./ft_printf/printlibft.a ft_printf/libft/libft.a -o client -Werror -Wall -Wextra

client:		${PRINTF} $(LIBFT) client.c
	gcc server.c ./ft_printf/printlibft.a ft_printf/libft/libft.a -o server -Werror -Wall -Wextra

clean:
	make clean -C ./ft_printf/libft
	make clean -C ./ft_printf
	$(RM) $(OBJS)

fclean: clean
	make fclean -C ./ft_printf/libft
	make fclean -C ./ft_printf
	$(RM) $(NAME)

re:			fclean all
				cd ${DIRLIB} && ${MAKE} clean
				cd ${DIRLIB2} && ${MAKE} clean

.PHONY:		all clean fclean re client
