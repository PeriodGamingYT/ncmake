clean:
	rm -f ncmake

make: main.c
	clear
	make clean
	gcc -o ncmake main.c

# NOTE: This only works on unix-like systems!
install:
	make
	sudo cp ncmake /usr/local/bin
