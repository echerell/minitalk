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

.PHONY: all clean fclean re

all: $(SERVER) $(CLIENT)

$(SERVER):
	$(CC) $(CFLAGS) -c $(SERVER_SRC) $(UTILS_SRC) -I.
	$(CC) $(SERVER_OBJ) $(UTILS_OBJ) -o $(SERVER)

$(CLIENT):
	$(CC) $(CFLAGS) -c $(CLIENT_SRC) $(UTILS_SRC) -I.
	$(CC) $(CLIENT_OBJ) $(UTILS_OBJ) -o $(CLIENT)

clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ) $(UTILS_OBJ)

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all
