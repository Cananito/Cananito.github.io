CFLAGS=-Wall -Wextra -Werror

run: generator
	./generator

build: generator

generator: entity.o md4c.o md4c-html.o mdcontent.o scorecards.o generator.o
	$(CC) -g $(CFLAGS) entity.o md4c.o md4c-html.o mdcontent.o scorecards.o generator.o -o generator

entity.o: md4c/src/entity.c
	$(CC) -g $(CFLAGS) -c md4c/src/entity.c -o entity.o

md4c.o: md4c/src/md4c.c
	$(CC) -g $(CFLAGS) -Wno-macro-redefined -c md4c/src/md4c.c -o md4c.o

md4c-html.o: md4c/src/md4c-html.c
	$(CC) -g $(CFLAGS) -c md4c/src/md4c-html.c -o md4c-html.o

mdcontent.o: _generator/mdcontent.c
	$(CC) -g $(CFLAGS) -c _generator/mdcontent.c -o mdcontent.o

scorecards.o: _generator/scorecards.c
	$(CC) -g $(CFLAGS) -c _generator/scorecards.c -o scorecards.o

generator.o: _generator/generator.c
	$(CC) -g $(CFLAGS) -c _generator/generator.c -o generator.o

clean:
	rm -f *.o
	rm -f generator
	rm -rf generator.dSYM/
