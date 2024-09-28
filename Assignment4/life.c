#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ROWS 5
#define COLS 5
#define LIMIT 25

/*
atoi() => used to convert from string to integer when taking numbers located in a string
strtok() => used to tokenize strings until a delimiter (in this case a comma)
3 global variables: Boolean value for while, main board to be printed out, and 1D array for promptInitialState/potential reprompts
*/

typedef enum {F = 0, T = 1} Bool;
int lifeBoard[ROWS][COLS] = {0};
int singleArray[LIMIT];

void promptInitialState() {
    char initialInput[50];
    char* token;
    Bool reprompt = T;

    while(reprompt) {
        int count = 0;

        for(int i = 0; i < LIMIT; i++) {
            singleArray[i] = 0;
        }

        printf("Enter the offsets for the live cells: ");
        fgets(initialInput, sizeof(initialInput), stdin);

        if(initialInput[0] == ',') {
            count++;
        }

        for(int j = 1; j < strlen(initialInput); j++) {
            if(initialInput[j - 1] == ' ') {
                count++;
            }
            else if(isalpha(initialInput[j - 1])) {
                count++;
            }
            else if(ispunct(initialInput[j - 1]) && initialInput[j - 1] != ',') {
                count++;
            }
            else if(ispunct(initialInput[j - 1]) && ispunct(initialInput[j])) {
                count++;
            }
        }

        token = strtok(initialInput, ",");

        while(token != NULL) {
            if(atoi(token) < 0 || atoi(token) > 24) {
                count++;
            }

            singleArray[atoi(token)] = 1;
            token = strtok(NULL, ",");
        }

        if(count == 0) {
            reprompt = F;
        }
    }
}

void setInitialState(int board[][COLS], int initial_state[]) {
    int* initPtr = initial_state;
    int a = 0;

    for(int k = 0; k < ROWS; k++) {
        for(int l = 0; l < COLS; l++) {
            board[k][l] = *(initPtr + a);
            a++;
        }
    }
}

int countLiveNeighbors(int board[][COLS], int r, int c) {
    int counter = 0;

    for(int m = r - 1; m <= r + 1; m++) {
        for(int n = c - 1; n <= c + 1; n++) {
            if((m == r && n == c)) {
                continue;
            }
            if((m < 0 || n < 0) || (m >= ROWS || n >= COLS)) {
                continue;
            }
            if(board[m][n] == 1) {
                counter++;
            }
        }
    }

    return counter;
}

void nextGeneration(int board[][COLS]) {
    int tempBoard[ROWS][COLS];
    int liveNeighbors;

    for(int p = 0; p < ROWS; p++) {
        for(int q = 0; q < COLS; q++) {
            tempBoard[p][q] = board[p][q];
        }
    }


    for(int s = 0; s < ROWS; s++) {
        for(int t = 0; t < COLS; t++) {
            liveNeighbors = countLiveNeighbors(lifeBoard, s, t);
            if(tempBoard[s][t] == 1 && (liveNeighbors < 2 || liveNeighbors > 3)) {
                tempBoard[s][t] = 0;
            }

            if(tempBoard[s][t] == 0 && liveNeighbors == 3) {
                tempBoard[s][t] = 1;
            }
        }
    }

    for(int u = 0; u < ROWS; u++) {
        for(int v = 0; v < COLS; v++) {
            board[u][v] = tempBoard[u][v];
        }
    }
}

void printBoard(int board[][COLS]) {
    for(int w = 0; w < ROWS; w++) {
        for(int x = 0; x < COLS; x++) {
            printf("%d", board[w][x]);
        }
        printf("\n");
    }
}

void playGameOfLife() {
    promptInitialState();
    int generation = 0;
    setInitialState(lifeBoard, singleArray);

    while(generation < 7) {
        printf("Generation = %d\n", generation);
        if(generation == 0) {
            printBoard(lifeBoard);
        }
        else {
            nextGeneration(lifeBoard);
            printBoard(lifeBoard);
        }
        generation++;
    }
}

int main()
{
    char input[50];

    printf("Welcome! Press 'q' to quit or any other key to continue: ");
    scanf("%s", input);
    fflush(stdin);

    while(strcmp(input, "q") != 0) {
        playGameOfLife();
        printf("Press any key to start a new life or 'q' to quit: ");
        scanf("%s", input);
        fflush(stdin);
    }

    printf("Goodbye!");
    return 0;
}
