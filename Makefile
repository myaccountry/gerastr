static: libgerastr.a

libgerastr.a: gerastr.o
	ar rcs $@ $^

gerastr.o: gerastr.cpp gerastr.hpp
	g++ -c $< -o $@

clean:
	rm gerastr.o libgerastr.a

install:
	sudo cp libgerastr.a /usr/local/lib/ && sudo cp gerastr.hpp /usr/local/include/

all:
	make && make install && make clean