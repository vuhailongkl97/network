SRCS:= list_iface.c
OBJS:= $(patsubst %.c,%.o,$(SRCS))
TARGET:= t

.c.o:
	$(CC) $(SRCS) -c 

all:$(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET)
