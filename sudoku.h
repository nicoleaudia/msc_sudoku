#ifndef SUDOKU_H
#define SUDOKU_H

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);



/*purpose: checks if sudoku board is full (each element of the 9x9 array contains a value other than '.'). note that function does not check logical validity of characters.

returns: returns true if all values in the array are characters '1' through '9' and are not '.', indicating the board is complete. returns false if at least one space on board has a value that is not a character '1' through '9' or has the value '.', which represents a blank space.

parameters: 
@param board: a 9x9 array of characters that represents sudoku inputs as characters '1' through '9', and '.', representing a blank space.*/
bool is_complete(const char board[9][9]);



/*purpose: checks if an input is valid (within a set range) and legal (move is okay based on other values on the board and rules of sudoku -- no repeats within row, column, or minisquare). this function then loads the input value into the specified position on the board. 

returns: returns true if the input specified in @param digit and the board position specified in @param position constitute a valid and legal move for the sudoku board. returns false if the input is not valid or legal.

parameters:
@param position: a 2-element array of characters that represents a position on a sudoku board. To be valid, the first element should have a character value 'A' through 'I', and the second element should have a character value '1' through '9' (ex: I8 for the 9th row, 8th column of a board).
@param digit: a character representing a desired value on the sudoku board. To be valid, the character should be '1' through '9'.
@param board: a 9x9 array of characters that represents sudoku inputs as characters '1' through '9' and '.' (representing a blank space).*/
bool make_move(const char position[2], char digit, char board[9][9]);



/*purpose: use this function to convert the format of the value representing position on the sudoku board from a character array to a set of integers. 

returns: none (void function).

parameters:
@param position: a 2-element array of characters that represents a position on a sudoku board. To be valid, the first element should have a character value 'A' through 'I', and the second element should have a character value '1' through '9' (ex: I8 for the 9th row, 8th column of a board).
@param digit_row: an integer that represents a row of a sudoku board. the value of digit_row is calculated by converting the first element from the 2-element character array (@param position) into an integer.
@param digit_col: an integer that represents a column of a sudoku board. the value of digit_col is calculated by converting the second element from the 2-element character array (@param position) into an integer.*/
void row_converter(const char position[2], int& digit_row, int& digit_col);



/* purpose: checks validity of input for a sudoku board.

returns: returns true if values from @param position and @param digit are valid for sudoku. returns false if the first element of @param position is < 'A' or > 'I', if the second element is < '1' or > '9', or if @param digit is < '1' or > '9'.

parameters:
@param position: a 2-element array of characters that represents a position on a sudoku board. To be valid, the first element should have a character value 'A' through 'I', and the second element should have a character value '1' through '9' (ex: I8 for the 9th row, 8th column of a board).
@param digit: a character that represents a value on a sudoku board. to be valid, must be between '1' and '9'.*/
bool check_validity(const char position[2], char digit);



/* purpose: checks legality of input for a sudoku board.

returns: returns true if input can legally be played by  rules of sudoku. returns false if value in @param board is not '.' (meaning a value already exists at that position), or if there is a repeat value within the row, column, or 3x3 minisquare within the sudoku board.

parameters:
@param digit_row: an integer that represents a row of a sudoku board.
@param digit_col: an integer that represents a column of a sudoku board. 
@param digit: a character that represents a value on a sudoku board. to be valid, must be between '1' and '9'.
@param board: a 9x9 character array that represents sudoku inputs as characters '1' through '9', and '.', representing a blank space.*/
bool check_legality(int digit_row, int digit_col, char digit, char board[9][9]);



/*purpose: copies the contents of an array to an output file.

returns: returns true if contents of the array are copied to the output file. returns false if there's an error opening or closing the output file.

parameters:
@param filename: name of output file.
@param board: a 9x9 character array that represents sudoku inputs as characters '1' through '9', and '.', representing a blank space. */
bool save_board(const char* filename, char board[9][9]);



/*purpose: solves sudoku board (9x9 char array) using recursion.

returns: returns true if the board is solved, meaning a valid and legal character has been inputted in every position of the 9x9 array. returns false if every combination of inputs has been tried and no combination results in a completed legal/valid sudoku board.

paramaters:
@param board: a 9x9 character array that represents sudoku inputs as characters '1' through '9' and '.', representing a blank space.*/
bool solve_board(char board[9][9]);



/*purpose: find first '.' in an array, indicating a blank space on the sudoku board has been found.

returns: returns true if '.' is found, otherwise returns false.

parameters:
@param fill_row: an integer that represents a row of a sudoku board.
@param fill_col: an integer that represents a column of a sudoku board.
@param board: a 9x9 character array that represents sudoku inputs as characters '1' through '9' and '.', representing a blank space.*/
bool cell_empty(int& fill_row, int& fill_col, char board[9][9]);



/*purpose: solves sudoku board (9x9 char array) using recursion and measures performance by counting the number of times the function is called.

returns: returns true if the board is solved, meaning a valid and legal character has been inputted in every position of the 9x9 array. returns false if every combination of inputs has been tried and no combination results in a completed legal/valid sudoku board.

parameters:
@param board: a 9x9 array of characters that represents sudoku inputs as characters '1' through '9', and '.', representing a blank space.
@param call_count: an integer that increments each time the function is called.*/
bool solve_board_count(char board[9][9], int& call_count);

#endif
