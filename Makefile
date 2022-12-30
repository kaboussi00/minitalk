NAME = client
NAME1 = server
NAMEB = clientbonus
NAMEB1 = serverbonus
INC = minitalk.h
SRCS = client.c

SRCS1 = server.c

SRCS_B = clientbonus.c

SRCS_B1 = serverbonus.c

OBJS = $(SRCS:.c=.o)

OBJS1 = $(SRCS1:.c=.o)

OBJSB = $(SRCS_B:.c=.o)

OBJSB1 = $(SRCS_B1:.c=.o)

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

CC = cc

all:$(NAME) $(NAME1)

$(NAME):$(OBJS)

$(NAME1):$(OBJS1)

bonus:$(NAMEB) $(NAMEB1)

$(NAMEB):$(OBJSB)

$(NAMEB1):$(OBJSB1)

%.o:%.c $(INC)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS) $(OBJS1) $(OBJSB) $(OBJSB1)

fclean:clean
	$(RM) $(NAME) $(NAME1) $(NAMEB) $(NAMEB1)

re: fclean all