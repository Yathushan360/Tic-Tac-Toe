#include "tictactoe.h"

// --- Main Function ---
int main() {
    char board[10][10];
    int N;
    int gameMode;
    int currentPlayer = 1;
    int gameOver = 0;
    int row, col;
    char currentSymbol;

    // Seed the random number generator for computer moves
    srand(time(NULL));

    displayWelcome();
    N = getBoardSize();
    displayRules(N);
    gameMode = selectGameMode();

    initializeBoard(board, N);


// Create and initialize the log file
    FILE *file = fopen("tic-tac-toe_log.txt", "a");
    if (file != NULL) {
        fprintf(file, "--- New Game Log ---\nBoard Size: %dx%d, Game Mode: %d\n\n", N, N, gameMode);
        fclose(file);
    }


    // --- Game Loop ---
    while (!gameOver) {
        displayBoard(board, N);


        // Determine the current player's symbol
        if (gameMode >= 30) { // Any three-player mode
            if (currentPlayer == 1) currentSymbol = 'X';
            else if (currentPlayer == 2) currentSymbol = 'O';
            else currentSymbol = 'Z';
        } else { // Two-player modes
            currentSymbol = (currentPlayer == 1) ? 'X' : 'O';
        }

        // Determine if the current player is a human or a computer
        int isComputerTurn = 0;
        if (gameMode == 2 && currentPlayer == 2) { // Standard User vs Computer
            isComputerTurn = 1;
        } else if (gameMode == 31) { // 1 User vs 2 Computers
            if (currentPlayer == 2 || currentPlayer == 3) isComputerTurn = 1;
        } else if (gameMode == 32) { // 2 Users vs 1 Computer
            if (currentPlayer == 3) isComputerTurn = 1;
        }

        // Get the move from the correct source (human or computer)
        if (isComputerTurn) {
            printf("\nPlayer %d (Computer, '%c') is making a move...\n", currentPlayer, currentSymbol);
            getComputerMove(board, N, &row, &col);
        } else {
            getPlayerMove(currentPlayer, currentSymbol, board, N, &row, &col);
        }

    board[row][col] = currentSymbol;


  logMoveToFile(currentPlayer, row, col, currentSymbol);



        // Check for win or draw
        if (checkWin(board, N, currentSymbol)) {
            displayBoard(board, N);
            printf("\nPlayer %d wins!\n", currentPlayer);
            gameOver = 1;
        } else if (checkDraw(board, N)) {
            displayBoard(board, N);
            printf("\nMatch draw\n");
            gameOver = 1;
        } else {
            // Switch to the next player
            if (gameMode >= 30) { // Three-player modes
                currentPlayer = (currentPlayer % 3) + 1;
            } else { // Two-player modes
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
        }
    }

    return 0;
}

