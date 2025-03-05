CFLAGS=-Wall -Wextra -Werror

run: generator
	./generator

build: generator

generator: _generator/generator.c
	$(CC) -g $(CFLAGS) -c md4c/src/entity.c -o entity.o
	$(CC) -g $(CFLAGS) -Wno-macro-redefined -c md4c/src/md4c.c -o md4c.o
	$(CC) -g $(CFLAGS) -c md4c/src/md4c-html.c -o md4c-html.o
	$(CC) -g $(CFLAGS) -c _generator/generator.c -o generator.o
	$(CC) -g $(CFLAGS) entity.o md4c.o md4c-html.o generator.o -o generator

clean:
	rm -f *.o
	rm -f generator
	rm -rf generator.dSYM/
