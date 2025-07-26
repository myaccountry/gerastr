static: libgerastr.a

libgerastr.a: gerastr.o
	ar rcs $@ $^

gerastr.o: gerastr.cpp gerastr.h
	g++ -c $< -o $@

clean:
	rm gerastr.o libgerastr.a

install:
	sudo cp libgerastr.a /usr/local/lib/ && sudo cp gerastr.h /usr/local/include/

all:
	make && make install && make clean