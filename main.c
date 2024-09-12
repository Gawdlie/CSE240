#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define randomInRange(x, y) (rand() % y + x)

#define getUserInput(input) ({\
                             scanf("%s", input);\
                             fflush(stdin);\
                             })

char getPlayerMove() {
    char getPlayerMove[50];

    printf("Enter a move ('r' for rock, 'p' for paper, 's' for scissors): ");
    getUserInput(getPlayerMove);

    while(strcmp(getPlayerMove, "r") != 0 && strcmp(getPlayerMove, "p") != 0 && strcmp(getPlayerMove, "s") != 0) {
        printf("Invalid move! Please enter a proper move ('r' for rock, 'p' for paper, 's' for scissors): ");
        getUserInput(getPlayerMove);
    }

    return getPlayerMove[0];
}

char getComputerMove() {
    char computerMove[1];
	int randomNumber = randomInRange(1, 3);

	switch (randomNumber) {
        case 1:
            computerMove[0] = 'r';
            break;
        case 2:
            computerMove[0] = 'p';
            break;
        case 3:
            computerMove[0] = 's';
            break;
        default:
            printf("ERROR");
	}

	printf("Computer's Move: %c\n", computerMove[0]);
	return computerMove[0];
}

void playGame() {
    char playerMove = getPlayerMove();
    char computerMove = getComputerMove();
    bool gameInPlay = true;

    while(gameInPlay) {
        if(playerMove == 'r' && computerMove == 'p') {
            printf("You lose!\n");
        }
        else if(playerMove == 'r' && computerMove == 's') {
            printf("You win!\n");
        }
        else if(playerMove == 'p' && computerMove == 'r') {
            printf("You win!\n");
        }
        else if(playerMove == 'p' && computerMove == 's') {
            printf("You lose!\n");
        }
        else if(playerMove == 's' && computerMove == 'r') {
            printf("You lose!\n");
        }
        else if(playerMove == 's' && computerMove == 'p') {
            printf("You win!\n");
        }
        else {
            printf("Draw!\n");
        }
        gameInPlay = false;
    }
}

int main() {
    char userInput[50];

    printf("Welcome to Rock, Paper, Scissors! Press 'q' to quit or any other key to start: ");
    getUserInput(userInput);

    while(strcmp(userInput, "q") != 0) {
        playGame();
        printf("Press 'q' to quit or any other singular key to play again: ");
        getUserInput(userInput);
    }

    printf("Goodbye!");
    return 0;
}
