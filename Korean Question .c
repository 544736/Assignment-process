#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_Q 10
#define QUIZ_Q 5
#define LEN 100

typedef struct {
    int id;
    char question[LEN];
    char answer[LEN];
} KoreanQuestion;

typedef struct {
    char name[LEN], nickname[LEN], nationality[LEN];
    int score;
    char pass; // 'P' or 'F'
} Trainee;

typedef struct {
    int id;
    char correctness; // 'O' or 'X'
} QuizAnswer;

KoreanQuestion qbank[MAX_Q] = {
    {1, "How do you say 'Hello' in Korean?", "안녕하세요"},
    {2, "How do you say 'Thank you' in Korean?", "감사합니다"},
    {3, "How do you say 'Yes' in Korean?", "네"},
    {4, "How do you say 'No' in Korean?", "아니요"},
    {5, "How do you say 'Goodbye' in Korean?", "안녕히 가세요"},
    {6, "How do you say 'Sorry' in Korean?", "죄송합니다"},
    {7, "How do you say 'Excuse me' in Korean?", "실례합니다"},
    {8, "How do you say 'Love' in Korean?", "사랑"},
    {9, "How do you say 'Delicious' in Korean?", "맛있어요"},
    {10, "How do you say 'I don’t know' in Korean?", "모르겠어요"}
};

Trainee trainees[4] = {
    {"Kim Minji", "minji", "Korean", 0, 'F'},
    {"Alex Chen", "alex", "Canadian", 0, 'F'},
    {"John Smith", "john", "American", 0, 'F'},
    {"Liam Brown", "liam", "British", 0, 'F'}
};

char isAnswer(KoreanQuestion *q, const char *a) {
    return strcmp(q->answer, a) == 0 ? 'O' : 'X';
}

Trainee* selectRandomTaker() {
    int i, r, tries = 0;
    srand((unsigned int)time(NULL));
    while (tries++ < 100) {
        r = rand() % 4;
        if (strcmp(trainees[r].nationality, "Korean") != 0)
            return &trainees[r];
    }
    return NULL;
}

void serveRandomQuiz(Trainee *taker) {
    int used[MAX_Q] = {0}, i, id, score = 0;
    char input[LEN];
    QuizAnswer answers[QUIZ_Q];

    printf("The quiz will begin in 30 seconds...\n");
    sleep(30);
    srand((unsigned int)time(NULL));

    for (i = 0; i < QUIZ_Q; i++) {
        do id = rand() % MAX_Q; while (used[id]);
        used[id] = 1;
        printf("Q%d: %s\n> ", i+1, qbank[id].question);
        fgets(input, LEN, stdin);
        input[strcspn(input, "\n")] = 0;
        answers[i].id = qbank[id].id;
        answers[i].correctness = isAnswer(&qbank[id], input);
        if (answers[i].correctness == 'O') score += 20;
    }

    taker->score = score;
    taker->pass = (score >= 80) ? 'P' : 'F';

    printf("\n=== Result for %s ===\n", taker->name);
    for (i = 0; i < QUIZ_Q; i++)
        printf("Q%d: %c\n", i + 1, answers[i].correctness);
    printf("Total Score: %d\nStatus: %s\n\n", score, taker->pass == 'P' ? "Pass" : "Fail");
}

void testKoreanLang() {
    Trainee *t = selectRandomTaker();
    if (t) {
        printf("Welcome, %s, to the Korean quiz session!\n", t->name);
        serveRandomQuiz(t);
    } else {
        printf("No eligible trainee found.\n");
    }
}

int main() {
    testKoreanLang();
    return 0;
}
