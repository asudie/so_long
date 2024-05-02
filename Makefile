NAME = so_long
CC = cc
CFLAGS = -Wall -Werror -Wextra 
ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx
else
	INCLUDES = -I/opt/X11/include -Imlx
endif
 
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
ifeq ($(shell uname), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif
 
# [...]
 
all: 
# $(MLX_LIB) $(NAME)

test:
	cd libft; make
	$(CC) $(CFLAGS) -g so_long.c validate_map.c parser.c libft/libft.a gnl/get_next_line.c gnl/get_next_line_utils.c

$(NAME) : $(ARCHIVE)
	cd libft; make
	cd printf; make
	$(CC) *.c libft/libft.a printf/libftprintf.a  -o $@
 
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)
 
# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)
 
$(MLX_LIB):
	@make -C $(MLX_DIR)

clean :
	rm -rf *.dSYM a.out *.o
	cd libft && $(MAKE) clean

.PHONY : all clean fclean re