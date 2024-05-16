NAME = so_long
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
ifeq ($(shell uname), Linux)
 INCLUDES = -I/usr/include -Imlx_linux -Ilibft/
else
 INCLUDES = -I/opt/X11/include -Imlx -Ilibft/
endif
 
MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
LIBS = -Llibft -lft
MAKE_LIB = ar -rcs

# MLX_LIBS_LINUX = -L$(MLX_F) -lmlx_Linux -I$(MLX_F)/mlx.h -lXext -lX11 -lm  -L/usr/lib/X11 -lm -lz

ifeq ($(shell uname), Linux)
 MLX_FLAGS = -Lmlx -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lXpm -lXrandr -lm -lz
else
 MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

SRCS = so_long.c validate_map.c parser.c gnl/get_next_line.c gnl/get_next_line_utils.c minilibx-linux/*.c
OBJS = $(SRCS:.c=.o)
 
# [...]
 
all: $(MLX_LIB) $(NAME)

$(NAME) : $(ARCHIVE)
	cd libft; make
	$(CC) -g $(SRCS) libft/libft.a $(MLX_FLAGS) -o $@

$(ARCHIVE) : $(OBJS)
	$(MAKE_LIB) $(ARCHIVE) $^

test:
	cd libft; make
	$(CC) $(CFLAGS) -g so_long.c validate_map.c parser.c libft/libft.a gnl/get_next_line.c gnl/get_next_line_utils.c
 
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)
 
# $(NAME): $(OBJS)
#  $(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)
 
$(MLX_LIB):
	@make -C $(MLX_DIR)

clean :
	rm -rf *.dSYM a.out *.o so_long
	cd libft && $(MAKE) clean
	cd minilibx-linux && $(MAKE) clean

.PHONY : all clean fclean re