#include <stdio.h>
#include <string.h>

#define USAGE_MESSAGE	"Usage: %s <RELATIVE_PATH_TO_SCHEME> [SCHEME_FILENAME=RELATIVE_PATH_TO_SCHEME]\n"
#define OOM_MESSAGE		"%s: error: out of memory\n"
#define LENGTH_MESSAGE	"%s: error: total file path exceeds 100 characters; please limit PATH_TO_COLOR_SCHEME to 80 characters"

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
	char instl_dir[111] = "~/.config/micro/colorschemes/";

	// check siz of file path
	if (strlen(instl_dir) + strlen(clr_schm) > 110) {
			fprintf(stderr, LENGTH_MESSAGE, argv[0]);
			return 1;
	}

	strcat(instl_dir, clr_schm);

	printf("installing to: %s\n", instl_dir);

	printf("installation complete\n");
	
	return 0;
}
