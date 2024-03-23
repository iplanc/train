#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Train {
	char* name;
	int ticket;
	char* stations;
};

int main(int argc, char* argv[]) {
	argc = 2; argv[1] = "2";
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
	struct Train trains[15];

	char* info;
	fscanf(f, "%s", info);
	printf("%s", info);
	for (int i = 0; i < 15; i++) {
		char* train_info = "";
		fscanf(f, "%s", train_info);
		printf("%s", train_info);
		//sscanf(train_info, "%s:%s:%s\n", trains[i].name, &trains[i].ticket, trains[i].stations);
		
		//printf("%s - %d - %s", trains[i].name, trains[i].ticket, trains[i].stations);
	}

	for (int i = 1; i <= atoi(argv[1]); i++) {
		char from = rand() % 26 + 'A';
		char dest = rand() % 26 + 'A';
		// printf("%c -> %c\n", from, dest);

		
	}

	return 0;
}