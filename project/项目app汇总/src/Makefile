SRC := $(wildcard *.c)#bmp.c jpg.c tc.c list.c main.c
HHN := $(filter-out jpg.c bmp.c,$(SRC))#bmp.c jpg.c 
SRC := $(filter jpg.c bmp.c,$(SRC))#bmp.c jpg.c 

OBJ = $(SRC:%.c=%.o)#bmp.o jpg.o list.o tc.o
CROSS = arm-linux-
CC = $(CROSS)gcc
CPPFLAGS += -I ./../inc
CPPFLAGS += -I /home/gec/abc/include

LDFLAGS += -L ../lib
LDFLAGS += -L /home/gec/abc/lib
LDFLAGS += -ljpeg
LDFLAGS += -lphoto
LDFLAGS += -lpthread
libphoto.so:$(OBJ)
	$(CC) -shared -fPIC -o libphoto.so $(OBJ) $(CPPFLAGS) $(LDFLAGS)
	mv $@ ../lib

main:main.c
	$(CC) $(HHN) -o $@ $(CPPFLAGS) $(LDFLAGS)
	mv $@ ..


$(OBJ):%.o:%.c
	$(CC) $^ -o $@ -c -fPIC $(CPPFLAGS) $(LDFLAGS)
	echo $(OBJ)

clean:
	$(RM) $(OBJ)
distclean:clean
	$(RM) ../lib/*.so

.PHONY:clean
