SERVER = server
CLIENT = client

SRC_SERV = server.c utils.c
OBJ_SERV = $(SRC_SERV:%.c=%.o)

SRC_CL = client.c utils.c
OBJ_CL = $(SRC_CL:%.c=%.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_SERV) minitalk.h
	$(CC) $(FLAGS) $(OBJ_SERV) -o $(SERVER)

$(CLIENT): $(OBJ_CL) minitalk.h
	$(CC) $(FLAGS) $(OBJ_CL) -o $(CLIENT)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ 

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(SERVER) $(CLIENT)

re: fclean all

.PHONY: clean fclean all re
