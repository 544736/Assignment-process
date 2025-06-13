#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_MEMBERS 10
#define MAX_TRAUMA_DESC 256
#define MAX_RESPONSE_LEN 101
#define MAX_QUESTIONS 5
#define MAX_COUNSEL_RESPONSES 30

typedef struct { char nickname[20]; int age; char trauma[MAX_TRAUMA_DESC]; } Trauma;
typedef struct { int id; char question[100]; } CounselingQuestion;
typedef struct { char nickname[20]; char question[100]; char response[MAX_RESPONSE_LEN]; } CounselingResponse;

Trauma memberTraumas[MAX_MEMBERS] = {
    {"Aria", 19, ""}, {"Juno", 21, ""}, {"Nico", 20, ""}, {"Mira", 18, ""}, {"Tae", 22, ""}
}; int traumaCount = 5;

const CounselingQuestion questions[MAX_QUESTIONS] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};

CounselingResponse counselingData[MAX_COUNSEL_RESPONSES]; int responseCount = 0;

int findMemberIndex(const char *n) {
    for (int i = 0; i < traumaCount; i++) if (!strcmp(n, memberTraumas[i].nickname)) return i;
    return -1;
}

void traumaInputMenu() {
    char nickname[20], input[256];
    while (1) {
        printf("\nEnter member nickname (or 'exit'): "); scanf("%s", nickname);
        if (!strcmp(nickname, "exit")) break;
        int idx = findMemberIndex(nickname);
        idx != -1
            ? (printf("Enter trauma description: "), getchar(),
               fgets(input, sizeof(input), stdin), input[strcspn(input, "\n")] = 0,
               strncpy(memberTraumas[idx].trauma, input, MAX_TRAUMA_DESC))
            : printf("Nickname not found.\n");
    }
}

void showMembersWithTrauma() {
    printf("\nMembers with trauma:\n");
    for (int i = 0; i < traumaCount; i++)
        if (strlen(memberTraumas[i].trauma)) printf("- %s\n", memberTraumas[i].nickname);
}

void startCounselingSession(const char *nickname) {
    int used[5] = {0}, asked = 0; char resp[MAX_RESPONSE_LEN];
    printf("\n-- Counseling for %s --\n", nickname);
    srand(time(NULL));
    while (asked < 3) {
        int q = rand() % MAX_QUESTIONS; if (used[q]) continue; used[q] = 1;
        printf("\nQ: %s\n", questions[q].question);
        do {
            printf("Response (max 100 chars): "); fgets(resp, sizeof(resp), stdin);
            resp[strcspn(resp, "\n")] = 0;
        } while (strlen(resp) == 0 || strlen(resp) >= MAX_RESPONSE_LEN);
        strcpy(counselingData[responseCount].nickname, nickname);
        strcpy(counselingData[responseCount].question, questions[q].question);
        strcpy(counselingData[responseCount++].response, resp);
        asked++;
    }
}

void counselingSessionMenu() {
    showMembersWithTrauma(); char nickname[20];
    printf("Enter nickname for session (or 'exit'): "); scanf("%s", nickname);
    if (!strcmp(nickname, "exit")) return;
    int idx = findMemberIndex(nickname);
    if (idx == -1 || strlen(memberTraumas[idx].trauma) == 0)
        printf("Invalid or no trauma recorded.\n");
    else { getchar(); startCounselingSession(nickname); }
}

void overcomeTrauma() {
    char choice;
    do {
        printf("\n[Trauma Management Menu]\nA. Input Trauma\nB. Counseling Session\nQ. Quit\nSelect: ");
        scanf(" %c", &choice); choice = tolower(choice);
        switch (choice) {
            case 'a': traumaInputMenu(); break;
            case 'b': counselingSessionMenu(); break;
            case 'q': return;
            default: printf("Invalid choice.\n");
        }
    } while (1);
}

int main() {
    overcomeTrauma(); return 0;
}
