BIN = main
all:$(BIN)

CROSS = arm-linux-
CC = $(CROSS)gcc

$(BIN):%:%.c tc.c bmp.c music.c
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS)
LDFLAGS += -lpthread
clean:
	$(RM) $(BIN)
