NAME = so_long
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
ifeq ($(shell uname), Linux)
 INCLUDES = -I/usr/include -Imlx_linux -Ilibft/
else
 INCLUDES = -I/opt/X11/include -Imlx -Ilibft/
endif

LIBS = -Llibft -lft
MAKE_LIB = ar -rcs

ifeq ($(shell uname), Linux)
 MLX_FLAGS = -lmlx -lXext -lX11
else
 MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

SRCS = so_long.c so_long_utils.c keys_work.c validate_map.c validate_utils.c parser.c parser_utils.c gnl/get_next_line.c gnl/get_next_line_utils.c my_printf/ft_printf.c my_printf/utils.c
OBJS = $(SRCS:.c=.o)
 
all: $(MLX_LIB) $(NAME)

$(NAME) : $(OBJS) $(ARCHIVE)
	cd libft; make
	$(CC) -g $(SRCS) libft/libft.a $(MLX_FLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)
 
$(MLX_LIB):
	@make -C $(MLX_DIR)

clean :
	rm -rf *.dSYM a.out *.o
	cd libft && $(MAKE) clean
	cd my_printf && $(MAKE) clean

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re