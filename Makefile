CC = clang
CFLAGS = -std=c11 -Wall
LDFLAGS = -lncurses

SRCS = src/main.c \
	   src/game.c \
	   src/entities/entity.c \
	   src/entities/snake.c \
	   src/entities/apple.c
	   
OBJS = $(SRCS:.c=.o)
TARGET = snake_in_c

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
