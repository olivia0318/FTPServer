SRCS:=$(wildcard *.c)
OBJS:= $(SRCS:%.c=%.o)
ELF:=tcpClient
$(ELF):$(OBJS)
	gcc -Wall $^ -o $@ -lcrypt
clean:
	rm -rf $(ELF) $(OBJS)
