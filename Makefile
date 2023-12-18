CLIENTNAME = client
SERVERNAME = server
BONUS = bonus
LIBFT = ./libft/libft.a
LIBFTDIR = libft

CC = cc
CFLAGS = -Wextra -Werror -Wall
# LDFLAGS = -L/Users/msavina/libft/retry_libft/libft.a

RM = /bin/rm -f

SRC_C = client.c
SRC_S = server.c

# BONUS_SRCS = bonus_client.c bonus_server.c

CLIENTOBJS = $(SRC_C:%.c=%.o)
SERVEROBJS = $(SRC_S:%.c=%.o)
# OBJS = $(patsubst %.c, %.o, $(SRCS))
# BONUS_OBJS = $(BONUS_SRCS:%.c=%.o)

all :  $(CLIENTNAME) $(SERVERNAME)

makelibft:
	@if [ ! -f "$(LIBFT)" ]; then \
		OUTPUT=$$(make -C $(LIBFTDIR) --no-print-directory 2>&1); \
		# if echo "$$OUTPUT" | grep -E "cc|ar" > /dev/null; then \
		# 	echo "\033[0;32mLIBFT OK!\033[0m"; \
		# fi; \
	fi

$(CLIENTNAME) : $(CLIENTOBJS)
	$(CC) $(CFLAGS) -o $(SRC_C) -L$(LIBFTDIR) -lft

$(SERVERNAME) : $(SERVEROBJS)
	$(CC) $(CFLAGS) -o $(SRC_S) -L$(LIBFTDIR) -lft

# bonus : $(BONUS) $(BONUS_OBJS) $(OBJS)

clean :
	$(RM) $(CLIENTOBJS) $(SERVEROBJS) $(BONUS_OBJS)

fclean : clean
	$(RM) $(CLIENTNAME) $(SERVERNAME)

re : fclean all

.PHONY: all bonus clean fclean re