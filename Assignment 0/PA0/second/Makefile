all:second

second: second.c
	gcc -Wall -Werror -fsanitize=address -o second second.c

clean:
	rm -rf second