CLIENTNAME = client
SERVERNAME = server
LIBFT = ./libft/libft.a
LIBFTDIR = libft

CC = cc
CFLAGS = -Wextra -Werror -Wall

RM = rm -f

SRC_C = client.c
SRC_S = server.c
SRC_CB = client_bonus.c
SRC_SB = server_bonus.c

CLIENTOBJS = $(SRC_C:.c=.o)
SERVEROBJS = $(SRC_S:.c=.o)
CLIENTOBJS_B = $(SRC_CB:.c=.o)
SERVEROBJS_B = $(SRC_SB:.c=.o)

all : makelibft $(CLIENTNAME) $(SERVERNAME)

makelibft :
	@if [ ! -f "$(LIBFT)" ]; then \
		make bonus -C $(LIBFTDIR); \
	fi

bonus: $(CLIENTNAME)_bonus $(SERVERNAME)_bonus

$(CLIENTNAME)_bonus : $(CLIENTOBJS_B)
	$(CC) $(CFLAGS) $(CLIENTOBJS_B) -o $(CLIENTNAME)_bonus -L$(LIBFTDIR) -lft

$(SERVERNAME)_bonus : $(SERVEROBJS_B)
	$(CC) $(CFLAGS) $(SERVEROBJS_B) -o $(SERVERNAME)_bonus -L$(LIBFTDIR) -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(CLIENTNAME) : $(CLIENTOBJS)
	$(CC) $(CFLAGS) $(CLIENTOBJS) -o $(CLIENTNAME) -L$(LIBFTDIR) -lft

$(SERVERNAME) : $(SERVEROBJS)
	$(CC) $(CFLAGS) $(SERVEROBJS) -o $(SERVERNAME) -L$(LIBFTDIR) -lft

clean :
	$(RM) $(CLIENTOBJS) $(SERVEROBJS) $(CLIENTOBJS_B) $(SERVEROBJS_B)

fclean : clean
	$(RM) $(CLIENTNAME) $(SERVERNAME)

re : fclean all

.PHONY: all bonus clean fclean re
