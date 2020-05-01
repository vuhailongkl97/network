.PHONY: client server all clean
CLIENT_SRC=client_udp.c
SERVER_SRC=server_udp.c


CLIENT_OBJ=$(patsubst %.c,%.o, $(CLIENT_SRC))
SERVER_OBJ=$(patsubst %.c,%.o, $(SERVER_SRC))

all: client server

client: $(CLIENT_OBJ)
	$(CC) $^ -o $@

server: $(SERVER_OBJ)
	$(CC) $^ -o $@

clean:
	rm -rf $(CLIENT_OBJ) $(SERVER_OBJ)
	rm -rf client server
    	
