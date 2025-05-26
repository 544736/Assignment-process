#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINE_WIDTH 109

void delay(int seconds);
void clear_screen();
void print_triangle_left(int height);
void print_triangle_right(int height);
void print_centered(const char *text);

int main() {
    char name[100];
    char date[11]; // Format: yyyy-mm-dd

    printf("[Please enter the current date in \"yyyy-mm-dd\" format]: ");
    if (scanf("%10s", date) != 1) {
        fprintf(stderr, "Failed to read date.\n");
        return 1;
    }

    printf("[Please enter your name]: ");
    if (scanf(" %[^\n]", name) != 1) {
        fprintf(stderr, "Failed to read name.\n");
        return 1;
    }

    printf("**The input has been processed successfully.**\n");

    delay(3);
    clear_screen();

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

    // Left triangle (right-angled)
    print_triangle_left(5);

    // Centered Splash Text
    print_centered("[Magrathea ver 0.1]");
    print_centered("Magrathea, where a shining planet is created in a wasteland with no grass,");
    print_centered("a place where unseen potential is discovered and gems are polished by the hands of experts,");
    print_centered("Welcome to Magrathea.");

    // Right triangle (inverted right-angled)
    print_triangle_right(5);

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

    printf("[User]: %s", name);
    int spacing = LINE_WIDTH - (int)(strlen(name) + strlen(date) + 24); // spacing between two labels
    for (int i = 0; i < spacing; i++) putchar(' ');
    printf("[Execution Time]: %s\n", date);

    printf("=============================================================================================================\n");

    return 0;
}

void delay(int seconds) {
    time_t start_time = time(NULL);
    while (time(NULL) - start_time < seconds);
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void print_centered(const char *text) {
    int padding = (LINE_WIDTH - (int)strlen(text)) / 2;
    for (int i = 0; i < padding; i++) putchar(' ');
    printf("%s\n", text);
}

void print_triangle_left(int height) {
    for (int i = 1; i <= height; i++) {
        printf("*");
        for (int j = 1; j < i; j++) {
            printf("*");
        }
        putchar('\n');
    }
}

void print_triangle_right(int height) {
    for (int i = height; i >= 1; i--) {
        for (int j = 0; j < LINE_WIDTH - i; j++) putchar(' ');
        for (int j = 0; j < i; j++) putchar('*');
        putchar('\n');
    }
}
