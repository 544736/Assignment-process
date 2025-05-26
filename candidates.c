#include <stdio.h>
#include <stdlib.h>

#define CANDIDATE_COUNT 6
#define INFO_COUNT 11

char *member_info[INFO_COUNT] = {
    "Name", "Date of Birth", "Gender", "Email", "Nationality",
    "BMI", "Primary Skill", "Secondary Skill", "Korean Proficiency Level",
    "MBTI", "Introduction"
};

char candidate01[INFO_COUNT][100];
char candidate02[INFO_COUNT][100];
char candidate03[INFO_COUNT][100];
char candidate04[INFO_COUNT][100];
char candidate05[INFO_COUNT][100];
char candidate06[INFO_COUNT][100];
char (*candidates[CANDIDATE_COUNT])[100] = {
    candidate01, candidate02, candidate03, candidate04, candidate05, candidate06
};

// Helper function to convert DOB to age
int calculate_age(const char *dob) {
    int year, month, day;
    sscanf(dob, "%d/%d/%d", &year, &month, &day);
    return 2025 - year;
}

// Helper function to convert TOPIK level to string
const char* topik_level(const char* level) {
    if (level[0] == '0') return "Native";
    return level;
}

int main() {
    char group_name[50];
    int i = 0;

    // Get group name using getchar (bonus)
    printf("Enter the audition group name (e.g., Milliways): ");
    int ch, index = 0;
    while ((ch = getchar()) != '\n' && ch != EOF && index < 49) {
        group_name[index++] = (char)ch;
    }
    group_name[index] = '\0';

    printf("\n####################################\n");
    printf("     Audition Candidate Data Entry [%s]\n", group_name);
    printf("####################################\n");

    while (i < CANDIDATE_COUNT) {
        printf("\nEntering information for candidate #%d.\n", i + 1);
        printf("---------------------------------\n");
        int j;
        for (j = 0; j < INFO_COUNT; j++) {
            printf("%d. %s: ", j + 1, member_info[j]);
            fgets(candidates[i][j], 100, stdin);

            // Remove newline character if exists
            int len = 0;
            while (candidates[i][j][len] != '\0') {
                if (candidates[i][j][len] == '\n') {
                    candidates[i][j][len] = '\0';
                    break;
                }
                len++;
            }
        }
        i++;
        printf("=================================\n");
    }

    // Display results
    printf("\n####################################\n");
    printf("     Audition Candidate Data Review [%s]\n", group_name);
    printf("####################################\n");

    printf("====================================================================================================\n");
    printf("Name (Age)       | DOB       | Gender | Email                  | Nationality  | BMI  | Primary Skill | Secondary Skill | TOPIK   | MBTI  |\n");
    printf("====================================================================================================\n");

    for (i = 0; i < CANDIDATE_COUNT; i++) {
        int age = calculate_age(candidates[i][1]);

        printf("%-15s (%2d) | %-9s | %-6s | %-22s | %-12s | %-4s | %-13s | %-16s | %-7s | %-5s |\n",
            candidates[i][0], age, candidates[i][1], candidates[i][2], candidates[i][3],
            candidates[i][4], candidates[i][5], candidates[i][6], candidates[i][7],
            topik_level(candidates[i][8]), candidates[i][9]);

        printf("------------------------------------------------------------------------------------\n");
        printf("%s\n", candidates[i][10]);
        printf("------------------------------------------------------------------------------------\n");
    }

    return 0;
}
