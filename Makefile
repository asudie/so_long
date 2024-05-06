NAME = so_long
CC = cc
CFLAGS = -Wall -Werror -Wextra 
ifeq ($(shell uname), Linux)
 INCLUDES = -I/usr/include -Imlx -Ilibft/
else
 INCLUDES = -I/opt/X11/include -Imlx -Ilibft/
endif
 
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
LIBS = -Llibft -lft
MAKE_LIB = ar -rcs

ifeq ($(shell uname), Linux)
 MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
 MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

SRCS = so_long.c validate_map.c parser.c gnl/get_next_line.c gnl/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
 
# [...]
 
all: $(MLX_LIB) $(NAME)

$(NAME) : $(ARCHIVE)
	cd libft; make
	$(CC) $(SRCS) libft/libft.a $(MLX_FLAGS) -o $@

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
	rm -rf *.dSYM a.out *.o
	cd libft && $(MAKE) clean

.PHONY : all clean fclean re