TARGET = count-island

CC ?= gcc
RM = rm

CFLAGS += \
	-Wall -Wextra -Werror -pedantic -std=c11 \
	-I../common \
	-Iinclude

LDFLAGS +=

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

all: $(TARGET)

clean:
	$(RM) -f $(OBJECTS)

fclean: clean
	$(RM) -f $(TARGET)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: all clean fclean re
