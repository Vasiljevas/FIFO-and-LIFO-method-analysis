CC		= gcc
CFLAGS	= -g


all: queue

queue: ads.c
	$(CC) $(CFLAGS) -o run ads.c queue.c ads_proceduros.c