#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Node {
	char name;
	double cost;
};

int main() {
	FILE* f = fopen("./config", "w");
	struct Node nodes[26];
	double total_cost = 0.0;

	srand((unsigned)time(NULL));

	// generate stations info
	fputs("[STATIONS]\n", f);
	for (int i = 'A'; i <= 'Z'; i++) {
		nodes[i - 'A'].name = (char)i;
		nodes[i - 'A'].cost = (double)(rand() % 100) / 10;
		total_cost = total_cost + nodes[i - 'A'].cost;
		fprintf(f, "%c:%.1f\n", nodes[i - 'A'].name, nodes[i - 'A'].cost);
	}

	fputs("\n", f);

	// generate trains info
	fputs("[LINES]\n", f);
	for (int i = 1; i <= 15; i++) {
		int expected_cost = (int)(rand() % (int)total_cost - 20) + 20;
		char line[26] = "";

		// constantly random select stations and minus the cost until total_cost less than 0
		int total_stations = 26;
		struct Node nodes_copy[26]; memcpy(nodes_copy, nodes, sizeof(struct Node) * 26);

		while (expected_cost > 0) {
			if (total_stations == 0) break;
			
			int station_id = rand() % total_stations - 1;
			
			char temp[] = {nodes_copy[station_id].name, '\0'};
			strcat(line, temp);
			expected_cost = expected_cost - nodes_copy[station_id].cost;

			for (int k = station_id; k < total_stations; k++) {
				nodes_copy[k] = nodes_copy[k + 1];
			}

			total_stations = total_stations - 1;
		}

		fprintf(f, "K%02d:%d:%s\n", i, (int)(rand() % 100), line);
	}

	return 0;
}