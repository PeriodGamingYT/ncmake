make: main.c
	clear
	gcc -o ncmake main.c

clean:
	rm -f ncmake

# NOTE: This only works on unix-like systems!
install: ncmake
	sudo cp ncmake /usr/local/bin

uninstall:
	sudo rm -f /usr/local/bin/ncmake
