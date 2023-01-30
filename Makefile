make: main.c
	clear
	gcc -o main main.c

clean:
	rm -f main

run:
	make clean
	make
	./main

test: main
	rm -rf example
	./main example
	ls -a example
