#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MEMBERS 5
#define MAX_TESTS 7
#define MAX_NAME_LEN 30

const char *memberNames[MAX_MEMBERS] = {"Goeun", "Woncheol", "Youngjin", "Hyekyung", "Arthur"};
const char *nicknames[MAX_MEMBERS] = {"DanceQueen", "VocalKing", "VisualAce", "SilentPower", "Leader"};
const char *testNames[MAX_TESTS] = {
    "1-Mile Running", "Speed Sprint", "Push-ups", "Squats",
    "Arm Strength", "Swimming", "Weightlifting"
};

float fitness_data[MAX_MEMBERS * MAX_TESTS]; // 1D array

void setHealth() {
    char input[256];
    int i, j;
    printf("\n[Enter Fitness Data for Milliways Members]\n");
    for (i = 0; i < MAX_MEMBERS; ++i) {
        printf("Enter 7 scores for %s (%s), comma-separated:\n", memberNames[i], nicknames[i]);
        fgets(input, sizeof(input), stdin);
        char *token = strtok(input, ",");
        for (j = 0; j < MAX_TESTS && token != NULL; ++j) {
            fitness_data[i * MAX_TESTS + j] = atof(token);
            token = strtok(NULL, ",");
        }
    }
    printf("Fitness data saved.\n");
}

void getHealth() {
    int option, i, j;
    char input[64];
    printf("\n[View Fitness Data]\n1. All Data\n2. By Member\n3. Specific Test\n> ");
    fgets(input, sizeof(input), stdin);
    option = atoi(input);

    if (option == 1) {
        for (i = 0; i < MAX_MEMBERS; ++i) {
            printf("\n%s (%s):\n", memberNames[i], nicknames[i]);
            for (j = 0; j < MAX_TESTS; ++j)
                printf("%s: %.2f\n", testNames[j], fitness_data[i * MAX_TESTS + j]);
        }
    } else if (option == 2) {
        printf("Enter nickname: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        for (i = 0; i < MAX_MEMBERS; ++i) {
            if (strcmp(nicknames[i], input) == 0) {
                printf("\n%s (%s):\n", memberNames[i], nicknames[i]);
                for (j = 0; j < MAX_TESTS; ++j)
                    printf("%s: %.2f\n", testNames[j], fitness_data[i * MAX_TESTS + j]);
                return;
            }
        }
        printf("Nickname not found.\n");
    } else if (option == 3) {
        printf("Enter nickname: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        int found = -1;
        for (i = 0; i < MAX_MEMBERS; ++i)
            if (strcmp(nicknames[i], input) == 0) found = i;
        if (found == -1) {
            printf("Nickname not found.\n");
            return;
        }
        printf("Choose test (0-6):\n");
        for (j = 0; j < MAX_TESTS; ++j)
            printf("%d. %s\n", j, testNames[j]);
        fgets(input, sizeof(input), stdin);
        int test = atoi(input);
        if (test >= 0 && test < MAX_TESTS)
            printf("%s (%s) - %s: %.2f\n", memberNames[found], nicknames[found], testNames[test], fitness_data[found * MAX_TESTS + test]);
        else
            printf("Invalid test index.\n");
    } else {
        printf("Invalid selection.\n");
    }
}

void handleStage1() {
    char input[10];
    while (1) {
        printf("\n--- Stage 1: Physical Strength & Knowledge ---\n");
        printf("A. Enter Fitness Data\nB. View Fitness Data\nQ. Return\n> ");
        fgets(input, sizeof(input), stdin);
        if (tolower(input[0]) == 'q') break;
        else if (tolower(input[0]) == 'a') setHealth();
        else if (tolower(input[0]) == 'b') getHealth();
        else printf("Invalid input.\n");
    }
}
