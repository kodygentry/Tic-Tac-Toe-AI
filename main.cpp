#include <iostream>
#include <string>
#include "ABMiniMax.h"
#include "Node.h"
#include <vector>


const int PLAYER1 = 1, PLAYER2 = 2;
const char PLAYER1MOVE = 'X', PLAYER2MOVE = 'O';
const int GRID = 3; // value of size of board (ex. GRID 3 = 3x3. GRID 4 = 4x4)


// inititalize
void displayBoardLayout();
void displayBoard(std::vector<std::vector<char>> board);
void initializeBoard(std::vector<std::vector<char>> board);

// game logic
void startGame(int);
bool endGame(std::vector<std::vector<char>> board);
bool checkRow(std::vector<std::vector<char>> board);
bool checkCol(std::vector<std::vector<char>> board);
bool checkDiag(std::vector<std::vector<char>> board);
void declareWinner(int);

// AI implementation

int main(){
    std::cout << "\n---------------------------------------------------------------\n"
              << "\n\t\t\tTic-Tac-Toe\n"
              << "\n---------------------------------------------------------------\n";

    /*
        temp input loop
        later implement AI vs AI
    */
    char cont = 'n'; // used for continuing game or not
    do {
        char choice; // used for deciding who goes first
        std::cout << "Do you want to start first? (y/n) : ";
	 	std::cin >> choice;
        if(choice == 'n' || choice == 'N')
            startGame(PLAYER2);
        else if(choice == 'y' || choice == 'Y')
            startGame(PLAYER1);
        else
            std::cout << "Invalid input..." << std::endl;

        std::cout << "Keep playing? (y/n) : ";
        std::cin >> cont;
    } while(cont == 'y');
}


void displayBoardLayout(){
    std::cout << "\t\t\t 1 | 2 | 3 " << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t 4 | 5 | 6 " << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t 7 | 8 | 9 \n" << std::endl;
}

void displayBoard(std::vector<std::vector<char>> board){
    std::cout << "\t\t\t " << (board[0][0]) << " | " << (board[0][1]) << " | " << (board[0][2]) << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t " << (board[1][0]) << " | " << (board[1][1]) << " | " << (board[1][2]) << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t " << (board[2][0]) << " | " << (board[2][1]) << " | " << (board[2][2]) << std::endl;
}

void initializeBoard(std::vector<std::vector<char>> board){
    for (int i = 0; i < GRID; i++){
		for (int j = 0; j < GRID; j++)
			board[i][j] = ' ';
    }
}

void startGame(int turn){
  std::vector<std::vector<char>> board(GRID, std::vector<char>(GRID, ' '));
    int index = 0, row = 0, col = 0; // for depth index

    displayBoardLayout();

    while (endGame(board) == false && index != GRID * GRID){
        int n;

        // HUMAN INPUT
        std::cout << "\n\nEnter move = ";
        std::cin >> n;
        n--;
        row = n / GRID;
        col = n % GRID;
        if(board[row][col] == ' ' && n < 9 && n >= 0){
            char playerMove = (turn == PLAYER1) ? PLAYER1MOVE : PLAYER2MOVE;
            board[row][col] = playerMove;
            std::cout << "Player " << turn << " has put an " << playerMove << " in cell " << n+1 << "\n\n";
            displayBoard(board);
            index++;
            turn = (turn == PLAYER1) ? PLAYER2 : PLAYER1;
        } else if(board[row][col] != ' ' && n < 9 && n >= 0){
            std::cout << "\nPosition is occupied\n\n";
        } else if(n < 0 || n > 8){
            std::cout << "Invalid position\n";
        }
    }

    // draw
    if (endGame(board) == false && index == GRID * GRID) {
        std::cout << "Draw\n";
    } else {
        turn = (turn == PLAYER1) ? PLAYER2 : PLAYER1;

        declareWinner(turn);
    }
}

bool endGame(std::vector<std::vector<char>> board){
    return (checkDiag(board) || checkCol(board) || checkRow(board));
}

bool checkRow(std::vector<std::vector<char>> board) {
	for (int i = 0; i < GRID; i++) {
		if (board[i][0] == board[i][1] &&
			board[i][1] == board[i][2] &&
			board[i][0] != ' ')
			return (true);
	}
	return(false);
}

bool checkCol(std::vector<std::vector<char>> board) {
	for (int i = 0; i < GRID; i++) {
		if (board[0][i] == board[1][i] &&
			board[1][i] == board[2][i] &&
			board[0][i] != ' ')
			return (true);
	}
	return(false);
}

bool checkDiag(std::vector<std::vector<char>> board) {
	if (board[0][0] == board[1][1] &&
		board[1][1] == board[2][2] &&
		board[0][0] != ' ')
		return(true);

	if (board[0][2] == board[1][1] &&
		board[1][1] == board[2][0] &&
		board[0][2] != ' ')
		return(true);

	return(false);
}

void declareWinner(int turn){
	if (turn == PLAYER2)
		std::cout<<"PLAYER2 has won\n";
	else
		std::cout<<"PLAYER1 has won\n";
}

// AI Functions
