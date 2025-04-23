CC=cc
CFLAGS=-Wall -Wextra -Werror -Iheaders
LDFLAGS=-lpthread
TARGET=philo

SRCS= $(wildcard *.c */*.c)
OBJS= $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re