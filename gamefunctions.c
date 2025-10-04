// game.c

#include "gamefunctions.h" // Include the header file

// --- Function Implementations ---

/**
 * @brief Displays the welcome message.
 */
void displayWelcome() {
    printf("Welcome to the Game\n");
}

/**
 * @brief Prompts the user for the board size and validates it.
 * @return The validated board size (N).
 */
int getBoardSize() {
    int N;
    do {
        printf("Enter board size N (3<=N<=10): ");
        scanf("%d", &N);
        if (N < 3 || N > 10) {
            printf("Invalid size. Please enter a number between 3 and 10.\n");
        }
    } while (N < 3 || N > 10);
    return N;
}

/**
 * @brief Displays game rules and confirmation message.
 * @param N The size of the board.
 */
void displayRules(int N) {
    printf("\nYou selected a %dx%d board. To win, a player must get %d symbols in a row.\n\n", N, N, N);
    printf("Game Rules:\n");
    printf("  The game is played on an %d x %d grid.\n", N, N);
    printf("  Players take turns placing their symbol (X, O, or Z if 3-player mode).\n");
    printf("  The first player to get %d identical symbols in a row wins.\n", N);
    printf("  This can be horizontal, vertical, or diagonal.\n");
    printf("  If the board is completely filled and no player has won, the game ends in a draw.\n");
    printf("  If Three Player mode is used, at least one player must be a human.\n\n");
}

/**
 * @brief Prompts the user to select a game mode.
 * @return The selected game mode (1, 2, or 3).
 */
int selectGameMode() {
    int mode;
    do {
        printf("Select game mode:\n");
        printf("  1. Two Players (User vs User)\n");
        printf("  2. User vs Computer\n");
        printf("  3. Three Player\n");
        printf("Enter your choice: ");
        scanf("%d", &mode);
        if (mode < 1 || mode > 3) {
            printf("Invalid choice. Please select 1, 2, or 3.\n\n");
        }
    } while (mode < 1 || mode > 3);

    if (mode == 3) {
        int subMode;
        do {
            printf("\nSelect three-player mode:\n");
            printf("  1. One User vs Two Computers\n");
            printf("  2. Two Users vs One Computer\n");
            printf("  3. Three Users\n");
            printf("Enter your choice: ");
            scanf("%d", &subMode);
            if (subMode < 1 || subMode > 3) {
                printf("Invalid choice. Please select 1, 2, or 3.\n");
            }
        } while (subMode < 1 || subMode > 3);
        return 30 + subMode;
    }

    return mode;
}

/**
 * @brief Initializes the board with empty spaces.
 * @param board The 2D array representing the game board.
 * @param N The size of the board.
 */
void initializeBoard(char board[10][10], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = ' ';
        }
    }
}

/**
 * @brief Displays the current state of the game board with row and column numbers.
 * @param board The 2D array representing the game board.
 * @param N The size of the board.
 */
void displayBoard(char board[10][10], int N) {
    printf("\n");

    // Print column headers for easier coordinate selection
    printf("  "); // Alignment space
    for (int j = 0; j < N; j++) {
        printf("  %d ", j);
    }
    printf("\n");

    for (int i = 0; i < N; i++) {
        // Print the horizontal grid line
        printf("  +");
        for (int k = 0; k < N; k++) {
            printf("---+");
        }
        printf("\n");

        // Print the row number and the content of the cells
        printf("%d |", i);
        for (int j = 0; j < N; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n");
    }

    // Print the final bottom line of the grid
    printf("  +");
    for (int k = 0; k < N; k++) {
        printf("---+");
    }
    printf("\n\n");
}

/**
 * @brief Gets a move from a human player and validates it.
 * @param player The current player number.
 * @param symbol The current player's symbol.
 * @param board The game board.
 * @param N The size of the board.
 * @param row Pointer to store the row of the move.
 * @param col Pointer to store the column of the move.
 */
void getPlayerMove(int player, char symbol, char board[10][10], int N, int *row, int *col) {
    int validMove = 0;
    do {
        printf("\nPlayer %d ('%c'), enter your move (row col): ", player, symbol);
        scanf("%d %d", row, col);

        if (*row < 0 || *row >= N || *col < 0 || *col >= N) {
            printf("Invalid input: Move is outside the board boundaries.\n");
        } else if (board[*row][*col] != ' ') {
            printf("Invalid move: The cell is already occupied.\n");
        } else {
            validMove = 1;
        }
    } while (!validMove);
}

/**
 * @brief Generates a random valid move for the computer.
 * @param board The game board.
 * @param N The size of the board.
 * @param row Pointer to store the row of the move.
 * @param col Pointer to store the column of the move.
 */
void getComputerMove(char board[10][10], int N, int *row, int *col) {
    do {
        *row = rand() % N;
        *col = rand() % N;
    } while (board[*row][*col] != ' ');
}

/**
 * @brief Checks if the player with the given symbol has won.
 * @param board The game board.
 * @param N The size of the board.
 * @param symbol The symbol to check for a win.
 * @return 1 if the player has won, 0 otherwise.
 */
int checkWin(char board[10][10], int N, char symbol) {
    int i, j, count;

    // Check rows
    for (i = 0; i < N; i++) {
        count = 0;
        for (j = 0; j < N; j++) {
            if (board[i][j] == symbol) count++;
        }
        if (count == N) return 1;
    }

    // Check columns
    for (j = 0; j < N; j++) {
        count = 0;
        for (i = 0; i < N; i++) {
            if (board[i][j] == symbol) count++;
        }
        if (count == N) return 1;
    }

    // Check main diagonal (top-left to bottom-right)
    count = 0;
    for (i = 0; i < N; i++) {
        if (board[i][i] == symbol) count++;
    }
    if (count == N) return 1;

    // Check anti-diagonal (top-right to bottom-left)
    count = 0;
    for (i = 0; i < N; i++) {
        if (board[i][N - 1 - i] == symbol) count++;
    }
    if (count == N) return 1;

    return 0; // No win found
}

/**
 * @brief Checks if the game is a draw.
 * @param board The game board.
 * @param N The size of the board.
 * @return 1 if the game is a draw, 0 otherwise.
 */
int checkDraw(char board[10][10], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == ' ') {
                return 0; // Found an empty cell, so not a draw yet
            }
        }
    }
    return 1; // No empty cells found, it's a draw
}

/**
 * @brief Logs a player's move to a text file.
 * @param player The player number.
 * @param row The row of the move.
 * @param col The column of the move.
 * @param symbol The symbol placed.
 */
void logMoveToFile(int player, int row, int col, char symbol) {
    FILE *file = fopen("tic_tac_toe_log.txt", "a"); // "a" for append mode
    if (file == NULL) {
        printf("Error: Could not open log file.\n");
        return;
    }
    fprintf(file, "Player %d ('%c') moved to position (%d, %d)\n", player, symbol, row, col);
    fclose(file);
}

