#include <stdio.h>

#define FILENAME "buses.txt"

int main() {

    FILE *file;

    file = fopen(FILENAME, "r");

    if (file == NULL) {

        printf("Error! File \"" FILENAME "\" not found\n");
        return 1;
    }

    int routes_count = 0;

    fscanf(file, "%d", &routes_count);

    if (routes_count < 1) {

        printf("Error reading file or bus routes are not set correctly\n");
        return 2;
    }

    int stations[routes_count][2]; // station number and number of passengers on leaving

    /* Noob protection. If the user specifies the number of flights more than filled in the file. */
    for (size_t i = 0; i < routes_count; i++) {

        stations[i][1] = 0;
        stations[i][0] = (int)i;
    }

    int input = 0, output = 0; // the number of passengers input in the bus and output of the bus

    for(size_t i = 0; !feof(file) && i < routes_count; i++) {

        fscanf(file, "%d %d", &input, &output);

        if (i == 0) { // if this is the first station
            stations[i][1] = input; // number of passengers in the bus
            continue;
        }

        stations[i][1] = (stations[i-1][1] + input) - output; // number of passengers on leaving
    }

    /* Bubble sorting */
    for (size_t i = 0; i < routes_count - 1; i++) {

        for (size_t j = 0; j < routes_count - i - 1; j++) {

            if (stations[j][1] > stations[j + 1][1]) {

                int temp_num = stations[j][0];
                int temp_pas = stations[j][1];

                stations[j][0] = stations[j + 1][0];
                stations[j][1] = stations[j + 1][1];
                stations[j + 1][0] = temp_num;
                stations[j + 1][1] = temp_pas;
            }
        }
    }

    printf("Station\t Count\n");

    for (size_t i = 0; i < routes_count; i++)
        printf("%-7d\t %-5d\n", stations[i][0], stations[i][1]);

    fclose(file);
    return 0;
}
