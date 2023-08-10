CC = clang
CFLAGS = -std=c11 -Wall
LDFLAGS = -Lvendors/ncurses -lncurses

SRCS = src/main.c \
	   src/game.c \
	   src/utils.c \
	   src/clock.c \
	   src/languages.c \
	   src/ncurses_api.c \
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
