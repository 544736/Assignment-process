#include <stdio.h>
#include <string.h>

#define MAX_MEMBERS 10
#define DAYS 6
#define NAME_LEN 20

// Global exercise types
char *cardio[] = {"Running", "Cycling", "Fast Walking"};
char *full_body[] = {"Push-ups", "Squats"};
char *lower_body[] = {"Leg Press", "Leg Curl"};
char *upper_body[] = {"Pull-ups", "Chin-ups"};
char *core[] = {"Plank", "Crunches"};

char *days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Member nicknames
char member_nicknames[MAX_MEMBERS][NAME_LEN] = {
    "Aria", "Beom", "Chae", "Dune", "Eun", "Finn", "Gael", "Haru", "Ira", "Jin"
};

// Routine storage (1D array flattened: [member][day][2 exercises])
char member_routine[MAX_MEMBERS][DAYS][2][NAME_LEN];

// Function prototypes
void setExerciseRoutine();
void getExerciseRoutine();

int main() {
    int choice;
    while (1) {
        printf("\n--- Basic Workout Routine Menu ---\n");
        printf("1. Set Exercise Routine\n");
        printf("2. View Exercise Routine\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1: setExerciseRoutine(); break;
            case 2: getExerciseRoutine(); break;
            case 0: return 0;
            default: printf("Invalid choice.\n");
        }
    }
}

void setExerciseRoutine() {
    char nickname[NAME_LEN];
    int memberIndex = -1;
    int coreUsed = 0;

    printf("Enter member nickname: ");
    fgets(nickname, NAME_LEN, stdin);
    nickname[strcspn(nickname, "\n")] = '\0'; // remove newline

    // Find index
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(member_nicknames[i], nickname) == 0) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        printf("Member not found.\n");
        return;
    }

    printf("Setting workout routine for %s:\n", nickname);

    for (int d = 0; d < DAYS; d++) {
        printf("\n[%s]\n", days[d]);

        // 1. Cardio
        printf("Choose a Cardio (0: Running, 1: Cycling, 2: Fast Walking): ");
        int ci;
        scanf("%d", &ci);
        strcpy(member_routine[memberIndex][d][0], cardio[ci]);

        // 2. Strength/Core
        int type;
        printf("Choose exercise type (1: Full-body, 2: Lower-body, 3: Upper-body, 4: Core): ");
        scanf("%d", &type);

        if (type == 4) {
            if (coreUsed) {
                printf("Core already used this week. Choose another type.\n");
                d--; // redo the same day
                continue;
            }
            coreUsed = 1;
            int idx;
            printf("Core (0: Plank, 1: Crunches): ");
            scanf("%d", &idx);
            strcpy(member_routine[memberIndex][d][1], core[idx]);
        } else {
            int idx;
            switch (type) {
                case 1:
                    printf("Full-body (0: Push-ups, 1: Squats): ");
                    scanf("%d", &idx);
                    strcpy(member_routine[memberIndex][d][1], full_body[idx]);
                    break;
                case 2:
                    printf("Lower-body (0: Leg Press, 1: Leg Curl): ");
                    scanf("%d", &idx);
                    strcpy(member_routine[memberIndex][d][1], lower_body[idx]);
                    break;
                case 3:
                    printf("Upper-body (0: Pull-ups, 1: Chin-ups): ");
                    scanf("%d", &idx);
                    strcpy(member_routine[memberIndex][d][1], upper_body[idx]);
                    break;
                default:
                    printf("Invalid choice.\n");
                    d--;
                    continue;
            }
        }
    }

    printf("Workout routine set for %s!\n", nickname);
}

void getExerciseRoutine() {
    char nickname[NAME_LEN];
    int memberIndex = -1;

    printf("Enter member nickname to view routine: ");
    fgets(nickname, NAME_LEN, stdin);
    nickname[strcspn(nickname, "\n")] = '\0'; // remove newline

    // Find index
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(member_nicknames[i], nickname) == 0) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        printf("Member not found.\n");
        return;
    }

    printf("\n--- Weekly Workout for %s ---\n", nickname);
    for (int d = 0; d < DAYS; d++) {
        printf("%s: %s + %s\n", days[d],
               member_routine[memberIndex][d][0],
               member_routine[memberIndex][d][1]);
    }
}
