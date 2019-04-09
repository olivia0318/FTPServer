SRCS:=$(wildcard *.c)
OBJS:= $(SRCS:%.c=%.o)
ELF:=server_pthread_pool
$(ELF):$(OBJS)
	gcc $^ -o $@ -lpthread
clean:
	rm -rf $(ELF) $(OBJS)
