CC=gcc
CFLAGS=-fPIC -fmessage-length=0 -grecord-gcc-switches -O2 -Wall -D_FORTIFY_SOURCE=2 -fstack-protector -funwind-tables -fasynchronous-unwind-tables -g 
LIBS=-lmagic
all:
	$(CC) -o no-magic-file-test $(LIBS) $(CFLAGS) no-magic-file-test.c
	./no-magic-file-test
