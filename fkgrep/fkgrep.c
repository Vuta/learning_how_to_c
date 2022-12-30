#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_MAX_LEN 80
#define LINE_MAX_LEN 2048

static void remove_newline(char* filename);
static void search(FILE* fp, char* term, char* filename);

int main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "You need to supply the search term.");

		return -1;
	}

	// TODO: Let user supply the search directory
	FILE* logfile_p = fopen("./files.txt", "r");
	if (logfile_p == NULL) {
		fprintf(stderr, "Cannot open logfiles");

		return -1;
	}

	char filename[FILENAME_MAX_LEN];
	while (fgets(filename, sizeof(filename), logfile_p) != NULL) {
		remove_newline(filename);
		FILE* path_fp = fopen(filename, "r");
		if (path_fp == NULL) {
			fprintf(stderr, "Cannot open %s", filename);

			return -1;
		}

		char* lines[argc];
		for (int i = 1; i < argc; i++) {
			char* term = argv[i];
			// TODO: Make this more efficient
			search(path_fp, term, filename);

			// reset pointer position after each interation
			rewind(path_fp);
		}

		fclose(path_fp);
	}

	fclose(logfile_p);

	return 0;
}

void remove_newline(char* filename) {
	filename[strcspn(filename, "\n")] = 0;
}

// TODO: Make the result to be similar to what grep returns
void search(FILE* fp, char* term, char* filename) {
	char line[LINE_MAX_LEN];
	while (fgets(line, sizeof(line), fp) != NULL) {
		if (strstr(line, term) != NULL) {
			printf("- File %s\n", filename);
			printf("'%s' found in %s", term, line);
		}
	}
}
