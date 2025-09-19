#include <stdio.h>
#include <stdlib.h>

char* createBoard(int n);

void initializeBoard(char* board, int n);

void displayBoard(char* board, int n);

void freeBoard(char* board);


int main() {
    int n;

    printf("Enter the size of the board (N x N, where N is between 3 and 10): ");
    scanf("%d", &n);

    if (n < 3 || n > 10) {
        printf("Error: Invalid board size. Please choose a number between 3 and 10.\n");
        return 1;
    }

    char* gameBoard = createBoard(n);
    if (gameBoard == NULL) {
        printf("Error: Failed to allocate memory for the game board.\n");
        return 1;
    }

    initializeBoard(gameBoard, n);

    printf("\n %d x %d Tic-Tac-Toe board\n", n, n);
    displayBoard(gameBoard, n);

    freeBoard(gameBoard);

    return 0;
}


char* createBoard(int n) {
    char* board = (char*)malloc(n * n * sizeof(char));
    return board;
}

void initializeBoard(char* board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i * n + j] = ' ';
        }
    }
}


void displayBoard(char* board, int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf(" %c ", board[i * n + j]);
            if (j < n - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < n - 1) {
            for (int k = 0; k < n; k++) {
                printf("---");
                if (k < n - 1) {
                    printf("+");
                }
            }
            printf("\n");
        }
    }
    printf("\n");
}


void freeBoard(char* board) {
    free(board);
}


