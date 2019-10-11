#common makefile header

DIR_INC = ../include


TARGET	= asr_offline_sample 

all:$(TARGET)

CROSS_COMPILE = 
CFLAGS = -g -Wall -I$(DIR_INC)
CFLAGS += -I /home/gec/cJSON

LDFLAGS += -L ../libs/x64/

LDFLAGS += -lmsc -lrt -ldl -lpthread  -lstdc++



$(TARGET):%:%.c
	$(CROSS_COMPILE)gcc $(CFLAGS) $^ -o $@ $(LDFLAGS)


clean:
	@rm -f *.o $(TARGET)

.PHONY:clean

#common makefile foot
