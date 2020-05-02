.PHONY: client server all clean
CLIENT_SRC=client_tcp.c
SERVER_SRC=server_tcp.c


CLIENT_OBJ=$(patsubst %.c,%.o, $(CLIENT_SRC))
SERVER_OBJ=$(patsubst %.c,%.o, $(SERVER_SRC))
FLAG:= -g

all: client server
.c.o:
	$(CC) -c $(FLAG) $<

client: $(CLIENT_OBJ)
	$(CC) $^ $(FLAG) -o $@

server: $(SERVER_OBJ)
	$(CC) $^ $(FLAG) -o $@

clean:
	rm -rf $(CLIENT_OBJ) $(SERVER_OBJ)
	rm -rf client server
