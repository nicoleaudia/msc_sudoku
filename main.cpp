#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];
 
  //This section illustrates the use of the pre-supplied helper functions. 
  cout << "============= Pre-supplied functions =============\n\n";

  cout << "Calling load_board():\n";
  load_board("easy.dat", board);

  cout << '\n';
	cout << "Displaying Sudoku board with display_board():\n";
  display_board(board);
  cout << "Done!\n\n"; 

  cout << "=================== Question 1 ===================\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n"; 

  cout << "=================== Question 2 ===================\n\n";


  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  // test non-valid position
  cout << "Putting '1' into K8 is ";
  if (!make_move("K8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  // test non-valid digit
  cout << "Putting '0' into I8 is ";
  if (!make_move("I8", '0', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  // test valid position and digit, but illegal move due to row conflict
  cout << "Putting '4' into B9 is ";
  if (!make_move("B9", '4', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  // test valid position and digit, but illegal move due to minisquare conflict
  cout << "Putting '2' into A2 is ";
  if (!make_move("A2", '2', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);
  

  cout << "=================== Question 3 ===================\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful.\n";
  } else {
    cout << "Save board failed.\n";
  }
  cout << '\n'; 

  cout << "=================== Question 4 ===================\n\n";

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:\n"; 
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  // test case where the loaded board has illegal move (in E9), thus puzzle is unsolvable
  load_board("mistake.dat", board);
  if (solve_board(board)) {
    cout << "The 'mistake' board has a solution:\n"; 
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  // test case where all spaces are blank ('.'), thus has multiple solutions
  // purpose of test is to see how a solution is reached (first row will be 123456789)
  load_board("blank.dat", board);
  if (solve_board(board)) {
    cout << "The 'blank' board has a solution:\n"; 
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  cout << "=================== Question 5 ===================\n\n";

  int call_count = 0;
  load_board("mystery1.dat", board);
  if (solve_board_count(board, call_count)) {
    cout << "The 'mystery1' board has a solution:\n"; 
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';
  cout << "The mystery1 board called the solve_board_count function " << call_count << " times.\n\n";


  call_count = 0;
  load_board("mystery2.dat", board);
  if (solve_board_count(board, call_count)) {
    cout << "The 'mystery2' board has a solution:\n"; 
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';
  cout << "The mystery2 board called the solve_board_count function " << call_count << " times.\n\n";

  
  call_count = 0;
  load_board("mystery3.dat", board);
  if (solve_board_count(board, call_count)) {
    cout << "The 'mystery3' board has a solution:\n"; 
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';
  cout << "The mystery3 board called the solve_board_count function " << call_count << " times.\n\n";
 
  return 0;
}
 
