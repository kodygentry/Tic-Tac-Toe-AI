#include <iostream>
#include <string>



const char COMPUTERMOVE = 'O', HUMAN = 'X';
const int GRID = 3; // value of size of board (ex. GRID 3 = 3x3. GRID 4 = 4x4)


void displayBoardLayout(){
    std::cout << "\t\t\t 1 | 2 | 3 " << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t 4 | 5 | 6 " << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t 7 | 8 | 9 \n" << std::endl;
}
void displayBoard(char board[][GRID]){
    std::cout << "\t\t\t " << (board[0][0]) << " | " << (board[0][1]) << " | " << (board[0][2]) << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t " << (board[1][0]) << " | " << (board[1][1]) << " | " << (board[1][2]) << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t " << (board[2][0]) << " | " << (board[2][1]) << " | " << (board[2][2]) << std::endl;
}   

void initializeBoard(char board[][GRID]){
    for (int i = 0; i < GRID; i++){
		for (int j = 0; j < GRID; j++) 
			board[i][j] = ' '; 
    }
}

int main(){
    char board[GRID][GRID];
    std::cout << "\n---------------------------------------------------------------\n"
              << "\n\t\t\tTic-Tac-Toe\n"
              << "\n---------------------------------------------------------------\n";
    displayBoardLayout();
    initializeBoard(board);
    displayBoard(board);     
    return 0;
}