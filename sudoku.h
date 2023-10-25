#ifndef SUDOKU_H
#define SUDOKU_H

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

bool is_complete(const char board[9][9]);
bool make_move(char position[2], char digit, char board[9][9]);
bool save_board(const char* filename, char board[9][9]);

#endif
