SOUR:=$(wildcard *.c)
ELF:=main
OBJS:=$(SOUR:%.c=%.o)
CFLAGS:=$(shell mysql_config --cflags)
$(ELF):$(OBJS)
	gcc $^ -o $@ $(CFLAGS) -lmysqlclient -lpthread -lcrypto
clean:
	rm -rf $(ELF) $(OBJS)
