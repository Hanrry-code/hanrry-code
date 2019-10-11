BIN = main
all:$(BIN)

CROSS = arm-linux-
CC = $(CROSS)gcc

$(BIN):%:%.c bmp.c music.c alsa_recorder.c
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS)
	
CPPFLAGS += -I /home/gec/cJSON
CPPFLAGS += -I /home/gec/tools/include

LDFLAGS += -lpthread
LDFLAGS += -L /home/gec/cJSON
LDFLAGS += -lcjson
LDFLAGS += -L /home/gec/tools/lib
LDFLAGS += -lasound
clean:
	$(RM) $(BIN)
