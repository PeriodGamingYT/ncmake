#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void die(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(-1);
}

void create_file(char *name, char *contents) {
	FILE *file = fopen(name, "w+");
	if(file == NULL) {
		die("Can't open file!");
	}
	
	fprintf(file, "%s", contents);
	fclose(file);
}

int main(int argc, char *argv[]) {
	if(argc != 2) {
		die("Usage: ncmake nonexistent_directory");
	}

	struct stat dir_stat = { 0 };
	if(stat(argv[1], &dir_stat) != -1) {
		die("Can't make project in existing directory");
	}

	mkdir(argv[1], 0777);
	chdir(argv[1]);
	create_file(".gitignore", "main");
	create_file("Makefile", "make: main.c\n\tgcc -o main main.c\n\nclean:\n\trm -f main\n\nrun:\n\tmake clean\n\tmake\n\tclear\n\t./main\n");
	create_file("main.c", "#include <stdio.h>\n\nint main() {\n\tprintf(\"It Works!\\n\");\n\treturn 0;\n}\n");
	return 0;
}
