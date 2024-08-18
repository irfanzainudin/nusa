exec = nusa.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	cp ./nusa.out /usr/local/bin/nusa

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o