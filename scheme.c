#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]) {
	if (argc == 1) {
        printf("usage:\n");
        printf("\tscheme.exe <POPULATION> [CONFIG_FILE] [-debug]\n");
        printf("param:\n");
        printf("\t POPULATION: in this simulation how many people will be transferd\n");
        printf("\tCONFIG_FILE: pre-generated train config file default using \"./config\"\n");
        return -1;
    }

    srand((unsigned)time(NULL));

    for (int i = 1; i <= atoi(argv[1]); i++) {
        char from = rand() % 26 + 'A';
        char dest = rand() % 26 + 'A';
        // printf("%c -> %c\n", from, dest);

        
    }

    return 0;
}