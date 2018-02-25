all:
	clang main.c -Wall -Werror -Wextra -pedantic -O3

clean:
	rm *.out
