CFLAGS += -W -Wall -Wextra -Werror

all: eight_queens

debug: CFLAGS += -DDEBUG
debug: all

clean:
	$(RM) eight_queens *~
