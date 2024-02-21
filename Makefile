CFLAGS=-Wall -Wextra -Werror -Wmissing-prototypes -Wnullable-to-nonnull-conversion

run: generator
	./generator

generator: _generator/generator.c
	clang -g $(CFLAGS) -o generator _generator/generator.c

clean:
	rm -f generator
	rm -rf generator.dSYM/
