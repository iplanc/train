#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Train {
	char name[3];
	char ticket[0];
	char stations[26];
};

struct Train trains[15];
FILE* result;

int is_include(char* source, char target) {
	if (strchr(source, target)) {
		return 1;
	}
	return 0;
}

int find_direct(char from, char dest, int write) {
	int lines = 0;
	for (int i = 0; i < 15; i++) {
		int has_from = is_include(trains[i].stations, from);
		int has_dest = is_include(trains[i].stations, dest);
		if ((has_from + has_dest == 2) && write) {
			fprintf(result, "%s[%c -> %c]\n", trains[i].name, from, dest);
			lines = lines + 1;
		}
	}
	return lines;
}

int find_transit(char from, char dest) {
	for (int i = 0; i < 15; i++) {
		int has_from = 0; int has_dest = 0;
		if (is_include(trains[i].stations, from)) {
			has_from = 1;
			for (int j = trains[i].stations[0]; j < strlen(trains[i].stations); j++) {
				for (int k = 0; k < 15; k++) {
					if (i == k) continue;
					has_dest = find_direct(j, dest, 0);
					if (has_from + (has_dest % 1) == 2) {
						fprintf(result, "%s[%c -> %c] & %s[%c -> %c]\n", trains[i].name, from, j, trains[k].name, j, dest);
						return 0;
					}
				}
			}
		}
	}
}

int main(int argc, char* argv[]) {
	//argc = 2; argv[1] = "10";
	if (argc == 1) {
		printf("usage:\n");
		printf("\tscheme.exe <POPULATION> [CONFIG_FILE] [--debug]\n");
		printf("param:\n");
		printf("\t POPULATION: in this simulation how many people will be transferd\n");
		printf("\tCONFIG_FILE: pre-generated train config file, default using \"./config\"\n");
		return -1;
	}

	srand((unsigned)time(NULL));

	FILE* f = fopen("./config", "r");
	result = fopen("./result", "w");
	fseek(f, 176, SEEK_SET); // 176 = 11 + 26 * 6 + 1 + 8

	for (int i = 0; i < 15; i++) {
		fscanf(f, "%[^':']:%[^':']:%s\n", trains[i].name, trains[i].ticket, trains[i].stations);
	}

	for (int i = 1; i <= atoi(argv[1]); i++) {
		char from = 'A';
		char dest = 'A';
		while (from == dest) {
			from = rand() % 26 + 'A';
			dest = rand() % 26 + 'A';
		}
		fprintf(result, "{%03d}<%c -> %c>\n", i, from, dest);

		// first, filter for one line train, if not found, then
		if (!find_direct(from, dest, 1)) {
			// second, filter for transit train
		 	find_transit(from, dest);
		}

		fprintf(result, "\n");
	}

	return 0;
}
