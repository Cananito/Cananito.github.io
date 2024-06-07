CFLAGS=-Wall -Wextra -Werror -Wmissing-prototypes -Wnullable-to-nonnull-conversion

run: generator
	./generator

build: generator

generator: _generator/generator.c
	clang -g $(CFLAGS) -c md4c/src/entity.c -o entity.o
	clang -g -Wno-macro-redefined -c md4c/src/md4c.c -o md4c.o
	clang -g $(CFLAGS) -c md4c/src/md4c-html.c -o md4c-html.o
	clang -g $(CFLAGS) -c _generator/generator.c -o generator.o
	clang -g $(CFLAGS) entity.o md4c.o md4c-html.o generator.o -o generator
	rm *.o

clean:
	rm -f *.o
	rm -f generator
	rm -rf generator.dSYM/
