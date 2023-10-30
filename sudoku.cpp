#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}



/* function to check if board is full */
bool is_complete(const char board[9][9]){
  for (int row = 0; row < 9; row++){
    for (int col = 0; col < 9; col++){
      if (board[row][col] == '.')
	return false;
    } 
  }
  return true;
}



/* function to check and load character into position on board */
bool make_move(const char position[2], char digit, char board[9][9]){

  int digit_row;
  int digit_col;

  //call helper function to convert position from char array to integers
  row_converter(position, digit_row, digit_col);

  //call helper functions to check validity and legality
  if (!check_validity(position, digit))
    return false;
  
  if (!check_legality(digit_row, digit_col, digit, board))
    return false;
  
  //load value into position on board
  board[digit_row][digit_col] = digit;

  return true;
} 



/* helper function to convert position from char array to integers */
void row_converter(const char position[2], int& digit_row, int& digit_col){
  digit_row = position[0] - 'A';
  digit_col = position[1] - '1';
  return ;
}



/* helper function to check validity of input */
bool check_validity(const char position[2], char digit){
  
  // check that position is within row range
  if (position[0] < 'A' || position[0] > 'I')
    return false;

  // check that position is within column range
  if (position[1] < '1' || position[1] > '9')
    return false;
  
  // check that character digit is 1-9
  if (digit < '1' || digit > '9')
    return false;
  
  return true;
}



/* helper funtion to check legality of input */
bool check_legality(int digit_row, int digit_col, char digit, char board[9][9]){  

  int row;
  int col;
  
  // check that space is empty
  if (board[digit_row][digit_col] != '.')
    return false;
  
  // check for repeat digit within row 
  row = digit_row;
    for (col = 0; col < 9 ; col++){
      if (board[row][col] == digit)
	return false;
    }

  // check for repeat digit within column
  col = digit_col;
  for (row = 0; row < 9 ; row++){
    if (board[row][col] == digit)
      return false;
    }

  // check for repeat within minisquare
  int minisquare_row, minisquare_col; //variables to mark the index of upper left corner of 3x3 minisquare

  minisquare_row = digit_row - digit_row%3;
  minisquare_col = digit_col - digit_col%3;

  for (row = minisquare_row; row < (minisquare_row + 3); row++){
    for (col = minisquare_col; col < (minisquare_col + 3); col++){
      if (board[row][col] == digit)
	return false;
    }
  }
  return true;
}



/* function to copy the contents of an array to an output file */
bool save_board(const char* filename, char board[9][9]){

  int row;
  int col;
  
  ofstream out;
  out.open(filename);

   if (out.fail())
    {
      return false;
    }
  
  for (row = 0; row < 9; row++){
    for (col = 0; col < 9; col++){
      out.put(board[row][col]);
    } 
    out << endl;
  }

  out.close();

  if (out.fail())
    {
      return false;
    }
  
  return true;
}



/* function to solve sudoku board using recursion */
bool solve_board(char board[9][9]){

  int fill_row, fill_col;

  //call helper function to find first empty space
  if (cell_empty(fill_row, fill_col, board)){
    char position[2] = {'A' + fill_row, '1' + fill_col};

    //try each possible move at that space. if board is solvable for this move, return true 
    //if board is not solvable for that move, place '.' (undo move) and loop back to check next move
    for (char input = '1'; input <= '9'; input++){
      if (make_move(position, input, board)){
	if (solve_board(board)) {
	  return true;
	}
	board[fill_row][fill_col] = '.';
      }          
    } 
    return false;
  }  
  else
    return true;
}



/* helper function to find first empty space */
bool cell_empty(int& fill_row, int& fill_col, char board[9][9]){
  for (fill_row = 0; fill_row < 9; fill_row++){
    for (fill_col = 0; fill_col < 9; fill_col++){
      if (board[fill_row][fill_col] == '.')
	return true;
    }
  }
  return false;
}



/* function to measure performance by counting the number of times the function is called to solve */
bool solve_board_count(char board[9][9], int& call_count){
  int fill_row, fill_col;

  call_count++;
  
  if (cell_empty(fill_row, fill_col, board)){ 
    char position[2] = {'A' + fill_row, '1' + fill_col};

    
    for (char input = '1'; input <= '9'; input++){
      if (make_move(position, input, board)){
	if (solve_board_count(board, call_count)) { 
	  return true;
	}
	board[fill_row][fill_col] = '.';
      }          
    } 
    return false;
  }  
  else
    return true;
}

