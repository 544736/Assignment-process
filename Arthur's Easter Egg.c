#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char keyword[10];
    char message[512];
} ArthurTrauma;

ArthurTrauma arthur = {
    "specter",
    "I confess. After graduating from university, I was blinded by the arrogance of starting a startup and recklessly blocked my friends' paths. I painfully learned that when I am the only one convinced by my idea, it leads to disastrous results. The past Arthur was a ghost of dogmatism and stubbornness."
};

void charToBinary(char c, char* binaryStr) {
    for (int i = 7; i >= 0; i--) binaryStr[7 - i] = ((c >> i) & 1) ? '1' : '0';
    binaryStr[8] = '\0';
}

int isRightChar(char c, const char* bin) {
    char tmp[9]; charToBinary(c, tmp);
    return strcmp(tmp, bin) == 0;
}

int isEasterEgg(const char* input) {
    return strcmp(input, arthur.keyword) == 0;
}

void find_easter_egg() {
    printf("<<Arthur's Easter Egg>>\n");
    char bin[7][9], rev[7][9], decoded[8], ch, final[20];
    for (int i = 0; i < 7; i++) charToBinary(arthur.keyword[i], bin[i]), strcpy(rev[6 - i], bin[i]);
    for (int i = 0; i < 7; i++) {
        printf("Enter character for binary %s: ", rev[i]);
        scanf(" %c", &ch);
        if (!isRightChar(ch, rev[i])) {
            printf("Incorrect. Try again.\n"); i--;
        } else decoded[i] = ch;
    }
    decoded[7] = '\0';
    printf("Combine the characters into a word: ");
    scanf("%s", final);
    if (isEasterEgg(final)) {
        printf("##Easter Egg Discovered!$$\n%s\n", arthur.message);
    } else printf("Incorrect keyword. Returning to menu.\n");
}

// Place this in your Self-Management and Teamwork menu logic:
void selfManagementMenu() {
    char input[20];
    printf("\n[2. Self-Management and Teamwork]\nEnter your name or option: ");
    scanf("%s", input);
    if (strcmp(input, "Arthur") == 0) {
        find_easter_egg();
        return;
    }
    // other menu options...
}
