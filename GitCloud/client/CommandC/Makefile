SRCS:=$(wildcard *.c)
OBJS:= $(SRCS:%.c=%.o)
ELF:=tcpClient
$(ELF):$(OBJS)
	gcc $^ -o $@
clean:
	rm -rf $(ELF) $(OBJS)
