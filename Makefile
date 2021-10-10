CC = gcc
CFLAGS = -Wall -Wextra -Werror
SERVER = server
CLIENT = client

SERVER_SRC = server.c
CLIENT_SRC = client.c
UTILS_SRC = utils.c

SERVER_OBJ = server.o
CLIENT_OBJ = client.o
UTILS_OBJ = utils.o

SERVER_BONUS_SRC = server_bonus.c
CLIENT_BONUS_SRC = client_bonus.c

SERVER_BONUS_OBJ = server_bonus.o
CLIENT_BONUS_OBJ = client_bonus.o

.PHONY: all bonus clean fclean re

all: $(SERVER) $(CLIENT)

$(SERVER):
	$(CC) $(CFLAGS) -c $(SERVER_SRC) $(UTILS_SRC) -I.
	$(CC) $(SERVER_OBJ) $(UTILS_OBJ) -o $(SERVER)

$(CLIENT):
	$(CC) $(CFLAGS) -c $(CLIENT_SRC) $(UTILS_SRC) -I.
	$(CC) $(CLIENT_OBJ) $(UTILS_OBJ) -o $(CLIENT)

bonus:
	$(CC) $(CFLAGS) -c $(SERVER_BONUS_SRC) $(UTILS_SRC) -I.
	$(CC) $(SERVER_BONUS_OBJ) $(UTILS_OBJ) -o $(SERVER)
	$(CC) $(CFLAGS) -c $(CLIENT_BONUS_SRC) $(UTILS_SRC) -I.
	$(CC) $(CLIENT_BONUS_OBJ) $(UTILS_OBJ) -o $(CLIENT)

clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ) $(UTILS_OBJ)
	rm -f $(SERVER_BONUS_OBJ) $(CLIENT_BONUS_OBJ) $(UTILS_OBJ)

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all
