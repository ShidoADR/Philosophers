NAME = philo

CC = cc

FLAGS = -Wall -Wextra -Werror -g -g3 -fsanitize=thread

INCLUDE = -I headers/

MAIN = philosophers.c

SRCS = $(MAIN) $(addprefix srcs/, ph_error_handler.c ph_lib.c)

OBJS_DIR = objs

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

all : $(NAME)

$(OBJS_DIR)/%.o : %.c
	@ mkdir -p '$(@D)'
	@ $(CC) $(FLAGS) -I/usr/include -c $< -o $@ $(INCLUDE)

$(NAME) : $(OBJS)
	@ $(CC) $(FLAGS) $(OBJS) -o $(NAME) $(INCLUDE)
	@ echo "\e[0;32mBuild success!\e[0m"

clean :
	@ rm -rf $(OBJS_DIR)

fclean : clean
	@ rm -f $(NAME)

re : fclean all

.PHONY :
	all clean fclean re
