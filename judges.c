#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define MAX_INPUT 1024

char judges_array[MAX_JUDGES][MAX_INPUT];

// Function to count number of commas in input (should be 6 for 7 fields)
int count_commas(const char *input) {
    int count = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == ',') count++;
    }
    return count;
}

int main() {
    char project[100];
    int total_judges;
    int selected_members;
    char input[MAX_INPUT];

    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");
    printf("Participating Project: ");
    fgets(project, sizeof(project), stdin);
    project[strcspn(project, "\n")] = '\0'; // Remove newline

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);
    getchar(); // consume newline

    printf("Number of Selected Members: ");
    scanf("%d", &selected_members);
    getchar(); // consume newline

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    int i = 0;
    while (i < total_judges) {
        printf("Judge %d: ", i + 1);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (count_commas(input) != 6) {
            printf("The input items are incorrect. Please enter them again.\n");
            continue;
        }

        strncpy(judges_array[i], input, MAX_INPUT);
        i++;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    char choice;
    printf("\"Should we check the judge information?\" (Y/N): ");
    scanf(" %c", &choice);
    getchar(); // consume newline

    if (choice == 'N') {
        printf("Program terminated.\n");
        return 0;
    }

    if (choice == 'Y') {
        printf("%s Should we check the judge information? Y\n", project);
        printf("####################################\n");
        printf("#        Display Judge Data        #\n");
        printf("####################################\n");

        for (int j = 0; j < total_judges; j++) {
            char name[100], gender[10], affiliation[100], title[100], expertise[50], email[100], phone[20];

            sscanf(judges_array[j], "%99[^,], %9[^,], %99[^,], %99[^,], %49[^,], %99[^,], %19[^"]",
                   name, gender, affiliation, title, expertise, email, phone);

            printf("[Judge %d]\n", j + 1);
            printf("Name: %s\n", name);
            printf("Gender: %s\n", gender);
            printf("Affiliation: %s\n", affiliation);
            printf("Title: %s\n", title);
            printf("Expertise: %s\n", expertise);
            printf("Email: %s\n", email);
            printf("Phone: %s\n", phone);
            printf("-----------------------------------\n");
        }
    }

    return 0;
}
