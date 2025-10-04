// game.h

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Function Prototypes ---
void displayWelcome();
int getBoardSize();
void displayRules(int N);
int selectGameMode();
void initializeBoard(char board[10][10], int N);
void displayBoard(char board[10][10], int N);
void getPlayerMove(int player, char symbol, char board[10][10], int N, int *row, int *col);
void getComputerMove(char board[10][10], int N, int *row, int *col);
int checkWin(char board[10][10], int N, char symbol);
int checkDraw(char board[10][10], int N);
void logMoveToFile(int player, int row, int col, char symbol);

#endif // GAME_H
