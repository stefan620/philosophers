NAME		=	philo

CC			=	cc
CFLAGS		= -pthread

SRCS		=	./src/philosophers.c \
				./src/routines.c \
				./src/routine_utils.c \
				./src/init.c \
				./src/cycle.c \
				./utils/argument_prep.c \
				./utils/tool_box.c 

OBJS		=	$(SRCS:.c=.o)

INCLUDES	=	-I ./includes

RM			=	rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re