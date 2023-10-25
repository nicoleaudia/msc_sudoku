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

/* add your functions here */

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
/* end of function */

/* SPLIT INTO HELPER FUNCTIONS AND CHECK IF EMPTY. NEEDS TO BE EMPTY...function to load (valid) character into position on board */
bool make_move(char position[2], char digit, char board[9][9]){

  int digit_row;
  int digit_col;
  int row;
  int col;

  // load input into vars for row and column. if invalid, stop (return false)
  if ((position[0] >= 'A' && position[0] <= 'I') && (position[1] >= '1' && position[1] <= '9')){
    digit_row = position[0] - 'A';
    digit_col = position[1] - '1';
  } 
  else
    return false;
 
  // check that digit is 1-9
  if (digit < '1' || digit > '9')
    return false;

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
  
  //load value into position on board
  board[digit_row][digit_col] = digit;

  return true;
} 
/* end of function */

/* function to copy the contents of the input file to an output file */
bool save_board(const char* filename, char board[9][9]){

  int row;
  int col;
  
  ofstream out;
  out.open(filename);

  for (row = 0; row < 9; row++){
    for (col = 0; col < 9; col++){
      out.put(board[row][col]);
    } 
    out << endl;
  }

  out.close();
  
  return true;
}


