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

void create_file(char *dir, char *name, char *contents) {
	printf("%s %s\n", dir, name);
	char *path = (char*) malloc(
		sizeof(char) * 
		(
			(int)strlen(dir) + 
			(int)strlen(name) + 
			1
		)
	);
	
	int i = 0;
	int past_i = 0;
	int path_length = (int)strlen(dir) + (int)strlen(name) + 1;
	char *slash = "/";
	#ifdef __WIN32
		slash[0] = '\\';
	#endif

	#define WRITE_TO_STRING(str) \
		past_i = i; \
		for(; i < (int)strlen(str) + past_i || i < path_length; i++) { \
			path[i] = str[i]; \
		}
	
	WRITE_TO_STRING(dir)
	WRITE_TO_STRING(slash)
	WRITE_TO_STRING(name)
	printf("%d %s\n", path_length, path);
	#undef WRITE_TO_STRING
	FILE *file = fopen(path, "w+");
	fprintf(file, "%s", contents);
	fclose(file);
	free(path);
}

int main(int argc, char *argv[]) {
	if(argc != 2) {
		die("Usage: ncmake nonexistant_directory");
	}

	struct stat dir_stat = { 0 };
	if(stat(argv[1], &dir_stat) != -1) {
		die("Can't make project in existing directory");
	}

	mkdir(argv[1], 0777);
	create_file(argv[1], ".gitignore", "main");
	create_file(argv[1], "Makefile", "make: main.c\n\tgcc -o main main.c\n\nclean:\n\trm -f main\n\nrun:\n\tmake clean\n\tmake\n\tclear\n\t./main\n");
	create_file(argv[1], "main.c", "#include <stdio.h>\n\nint main() {\n\tprintf(\"It Works!\\n\");\n\treturn 0;\n\t}\n");
	return 0;
}
