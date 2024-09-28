#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define randomNumberRange(x, y) (rand() % (y - x + 1) + x)
#define SIZE 5
#define DUMMYINT 50

typedef struct Player{
    char name[50];
    int guesses;
} Player;

Player playerArr[SIZE] = {
    {"", DUMMYINT},
    {"", DUMMYINT},
    {"", DUMMYINT},
    {"", DUMMYINT},
    {"", DUMMYINT},
    };


void printFile(FILE* fp) {
    // Source: C_FileIO.pdf in Canvas Slides
    if(fp == NULL){
        fprintf( stderr, "Cannot open %s.\n", "leaders.txt");
        exit(1);
    }

    for(int i = 0; i < SIZE; i++) {
        if(playerArr[i].guesses != DUMMYINT) {
            fprintf(fp, "%s made %d guesses!\n", playerArr[i].name, playerArr[i].guesses);
        }
    }
}

void reopenFile(FILE* fp) {
    char line[100];
    char name[50];
    int getGuess;
    char* token;
    int i = 0;

    // Source: C_FileIO.pdf in Canvas Slides
    if(fp == NULL){
        fprintf( stderr, "Cannot open %s.\n", "leaders.txt");
        exit(1);
    }

    while(fgets(line, sizeof(line), fp)) {
        printf("%s", line);
        token = strtok(line, " ");

        if(strcmp(playerArr[i].name, "") == 0) {
            strcpy(playerArr[i].name, token);
        }

        printf("%s\n", playerArr[i].name);

        // Each line is 4 words, 3rd word is the # of guesses
        for(int c = 0; token != NULL; c++) {
            if(c == 2) {
                getGuess = atoi(token);
            }
            token = strtok(NULL, " ");
        }

        if(playerArr[i].guesses == DUMMYINT){
            playerArr[i].guesses = getGuess;
        }

        printf("%d\n", playerArr[i].guesses);
        i++;
    }
}

// Source: <stdlib.h> https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
// Function used for qsort() to compare int values (guesses) stored in struct elements of array
int compare(const void *a, const void* b) {
    return ((Player*)a)->guesses - ((Player*)b)->guesses;
}

void addToArray(Player* player) {
    int pos = -1;

    // Find position
    for(int a = 0; a < SIZE; a++) {
        if(playerArr[a].guesses == DUMMYINT || playerArr[a].guesses > player->guesses) {
           pos = a;
        }
    }

    // Shift elements down to insert new player at index position whenever array is already filled
    if(pos != -1) {
        for(int b = SIZE - 1; b > pos; b--) {
            playerArr[b] = playerArr[b - 1];
        }

    strcpy(playerArr[pos].name, player->name);
    playerArr[pos].guesses = player->guesses;
    }

    // Sort array based on number of guesses
    qsort(playerArr, SIZE, sizeof(Player), compare);

    printf("Here are the current leaders: \n");
    for(int i = 0; i < SIZE; i++) {
        if(playerArr[i].guesses != DUMMYINT) {
            printf("%s with %d guesses!\n", playerArr[i].name, playerArr[i].guesses);
        }
    }
}

void startGuessingGame(Player* player) {
    srand(time(NULL));
    int randomNumber = randomNumberRange(10, 100);
    double squareRootRandomNumber = sqrt(randomNumber);
    int guess = 0;
    int attempts = 0;

    printf("%f is the square root of what number? (Range is 10-100): ", squareRootRandomNumber);
    scanf("%d", &guess);
    fflush(stdin);
    attempts++;

    while(guess != randomNumber) {
        if(guess > randomNumber) {
            printf("Too high, guess again: Guess a value between 10 and 100: ");
            scanf("%d", &guess);
            fflush(stdin);
        }
        else if(guess < randomNumber) {
            printf("Too low, guess again: Guess a value between 10 and 100: ");
            scanf("%d", &guess);
            fflush(stdin);
        }
        attempts++;
    }

    printf("You got it baby!\n");
    player->guesses = attempts;
    printf("You made %d guesses!\n", player->guesses);
}

int main()
{
    char input[50];
    FILE* fp = fopen("leaders.txt", "r");
    reopenFile(fp);

    printf("Welcome! Press 'q' to quit or any other key to continue: ");
    scanf("%s", input);
    fflush(stdin);

    while(strcmp(input, "q") != 0) {
        Player p;
        printf("Please enter your name to start: ");
        scanf("%s", p.name);
        fflush(stdin);

        startGuessingGame(&p);
        addToArray(&p);

        printf("Press 'q' to quit or any other key to continue: ");
        scanf("%s", input);
        fflush(stdin);
    }

    fp = fopen("leaders.txt", "w");
    printFile(fp);
    fclose(fp);

    printf("Goodbye!\n");
    return 0;
}
