CC = g++
FLAGS = -O3 -Wall -Wextra -Werror -pedantic-errors -std=c++17
OBJS = main.o
PROJNAME = projetLO21

$(PROJNAME): $(OBJS)
	$(CC) $(FLAGS) -o $(PROJNAME) $^

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(PROJNAME)
