SRCS:=$(wildcard *.c)
OBJS:= $(SRCS:%.c=%.o)
ELF:=client
$(ELF):$(OBJS)
	gcc -Wall $^ -o $@ -lcrypt -lpthread
clean:
	rm -rf $(ELF) $(OBJS)
