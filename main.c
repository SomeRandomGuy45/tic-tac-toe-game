#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

char inputData[9] = {
    '_','_','_',
    '_','_','_',
    '_','_','_'
};

char player_1 = 'x', player_2 = 'o';

void ai() {
    int randomIndex = rand() % 9;
    while (inputData[randomIndex] != '_') {
        randomIndex = rand() % 9;
    }
    inputData[randomIndex] = player_2;
}

int getInput() {
    printf("Choose a slot (1-9):\n");
    int input;
    scanf("%d", &input);
    --input;
    if (input < 0 || input >= 9) {
        printf("Invalid input! Please use a number between 1 and 9.\n");
        return -1;
    }
    if (inputData[input] != '_') {
        printf("Slot already taken! Please select a different slot.\n");
        return -1;
    }
    return input;
}

void printTable() {
    for (int i = 0; i < 9; i++) {
        printf("%c", inputData[i]);
        if ((i + 1) % 3 != 0) {
            printf("|");
        }
        if ((i + 1) % 3 == 0 && i != 8) {
            printf("\n");
        }
    }
    printf("\n");
}

bool checkWin(char player) {
    // Rows
    for (int i = 0; i < 9; i += 3) {
        if (inputData[i] == player && inputData[i + 1] == player && inputData[i + 2] == player) {
            return true;
        }
    }
    // Columns
    for (int i = 0; i < 3; i++) {
        if (inputData[i] == player && inputData[i + 3] == player && inputData[i + 6] == player) {
            return true;
        }
    }
    // Diagonals
    if (inputData[0] == player && inputData[4] == player && inputData[8] == player) {
        return true;
    }
    if (inputData[2] == player && inputData[4] == player && inputData[6] == player) {
        return true;
    }
    return false;
}

int main(int argc, char** argv) {
    srand(time(NULL));
    int playerStart = rand() % 2;
    printf("%s\n", (playerStart == 0 ? "You go first!" : "NPC goes first"));
    if (playerStart != 0)
    {
        ai();
    }
    while (1) {
        printTable();

        // Player 1 move
        int input = getInput();
        while (input == -1) {
            input = getInput();
        }
        inputData[input] = player_1;

        if (checkWin(player_1)) {
            printTable();
            printf("Player 1 (x) wins!\n");
            break;
        }

        // Check for a draw
        int counter = 0;
        for (int i = 0; i < 9; i++) {
            if (inputData[i] != '_') {
                ++counter;
            }
        }
        if (counter == 9) {
            printTable();
            printf("It's a draw!\n");
            break;
        }

        // AI move
        ai();
        if (checkWin(player_2)) {
            printTable();
            printf("Player 2 (o) wins!\n");
            break;
        }
    }
    return 0;
}
