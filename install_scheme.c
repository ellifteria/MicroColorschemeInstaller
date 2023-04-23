#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define USAGE_MESSAGE		"Usage: %s <USERNAME> <RELATIVE_PATH_TO_SCHEME> [SCHEME_FILENAME=RELATIVE_PATH_TO_SCHEME]\n"
#define OOM_MESSAGE		"%s: error: out of memory\n"
#define LENGTH_MESSAGE		"%s: error: total file path exceeds 100 characters; please limit PATH_TO_COLOR_SCHEME to %lu characters\n"
#define FILE_OPEN_MESSAGE	"%s: error: failed to open file: %s\n"

#define PATH_LENGTH	123

#ifndef USER
#	define USER "root"
#endif

int main(int argc, char* argv[]) {

	// check num args
	if (argc < 2) {
		fprintf(stderr, USAGE_MESSAGE, argv[0]);
		return 1;
	}

	// check if --help
	if (argc >= 2 && strcmp(argv[1], "--help") == 0) {
		fprintf(stderr, USAGE_MESSAGE, argv[0]);
		return 2;
	}

	// initialize paths
	char* clr_schm = argv[1];
	
	char* instl_file;
	if (argc == 3) {
		instl_file = argv[2];
	} else {
		instl_file = argv[1];
	}
	char instl_dir[PATH_LENGTH] = "/Users/";
	strcat(instl_dir, USER);
	strcat(instl_dir, "/.config/micro/colorschemes/");
	

	// check siz of file path
	if (strlen(instl_dir) + strlen(instl_file) > PATH_LENGTH -1) {
		fprintf(stderr, LENGTH_MESSAGE, argv[0], PATH_LENGTH - strlen(instl_dir) - 1);
		return 1;
	}

	FILE* in_file = fopen(clr_schm, "r");
	if (!in_file) {
		fprintf(stderr, FILE_OPEN_MESSAGE, argv[0], clr_schm);
		return 3;
	}

	strcat(instl_dir, instl_file);

	printf("installing to: %s\n", instl_dir);

	FILE* out_file = fopen(instl_dir, "w");
	if (!out_file) {
		fprintf(stderr, FILE_OPEN_MESSAGE, argv[0], instl_dir);
		return 3;
	}


	char nxt_char;

	while ( (nxt_char = fgetc(in_file)) != EOF) {
		fputc(nxt_char, out_file);
	}

	printf("installation complete\n");

	fclose(in_file);
	fclose(out_file);
	
	return 0;
}
