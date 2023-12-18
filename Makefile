CLIENTNAME = client
SERVERNAME = server
LIBFT = ./libft/libft.a
LIBFTDIR = libft

CC = cc
CFLAGS = -Wextra -Werror -Wall

RM = /bin/rm -f

SRC_C = client.c
SRC_S = server.c

CLIENTOBJS = $(SRC_C:.c=.o)
SERVEROBJS = $(SRC_S:.c=.o)

all : makelibft  $(CLIENTNAME) $(SERVERNAME)

makelibft:
	@if [ ! -f "$(LIBFT)" ]; then \
		make -C $(LIBFTDIR); \
	fi

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(CLIENTNAME) : $(CLIENTOBJS)
	$(CC) $(CFLAGS) $(CLIENTOBJS) -o $(CLIENTNAME) -L$(LIBFTDIR) -lft

$(SERVERNAME) : $(SERVEROBJS)
	$(CC) $(CFLAGS) $(SERVEROBJS) -o $(SERVERNAME) -L$(LIBFTDIR) -lft

clean :
	$(RM) $(CLIENTOBJS) $(SERVEROBJS)

fclean : clean
	$(RM) $(CLIENTNAME) $(SERVERNAME)

re : fclean all

.PHONY: all clean fclean re
