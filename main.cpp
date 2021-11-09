#include <iostream>
#include <string>
#include "ABMiniMax.h"
#include "Node.h"
#include <vector>


const int PLAYER1 = 1, PLAYER2 = 2;
const char PLAYER1MOVE = 'X', PLAYER2MOVE = 'O';
const int GRID = 3; // value of size of board (ex. GRID 3 = 3x3. GRID 4 = 4x4)


// inititalize
void header();
void displayBoardLayout();
void displayBoard(std::vector<std::vector<char>> board);

// game logic
void startGame(int);
bool winDetection(std::vector<std::vector<char>> board);

int main(){
	header();
	startGame(PLAYER1);
    /*char cont = 'n'; // used for continuing game or not
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
    } while(cont == 'y');*/
}

void header(){
    std::cout << "\n---------------------------------------------------------------\n"
            << "\n\t\t\tTic-Tac-Toe\n"
            << "\n---------------------------------------------------------------\n";
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

void startGame(int turn){
  std::vector<std::vector<char>> board(GRID, std::vector<char>(GRID, ' '));
    int index = 0, row = 0, col = 0; // for depth index
    displayBoardLayout();
    Node node = Node(board);
    AI aiMax(&node, false, 9, 'X');
    AI aiMin(&node, false, 9, 'O');

    while (winDetection(board) == false && index != GRID * GRID){
        if(turn == PLAYER1) {
            board = aiMax.playMove(board, index);
            std::cout << "X's move" << std::endl;
            displayBoard(board);
            turn = PLAYER2;
            /*int n;

            std::cout << "\n\nEnter move = ";
            std::cin >> n;
            n--;
            row = n / GRID;
            col = n % GRID;
            if(board[row][col] == ' ' && n < 9 && n >= 0){
                char playerMove = PLAYER1MOVE;
                board[row][col] = playerMove;
                std::cout << "Player " << turn << " has put an " << playerMove << " in cell " << n+1 << "\n\n";
                displayBoard(board);
                turn = PLAYER2;
            } else if(board[row][col] != ' ' && n < 9 && n >= 0){
                std::cout << "\nPosition is occupied\n\n";
            } else if(n < 0 || n > 8){
                std::cout << "Invalid position\n";
            }*/
        } else {
            board = aiMin.playMove(board, index);
            std::cout << "O's move" << std::endl;
            displayBoard(board);
            turn = PLAYER1;
        }
        index++;
    }

    // draw
    if (winDetection(board) == false && index == GRID * GRID) {
        std::cout << "Draw\n";
    } else {
        turn = (turn == PLAYER1) ? PLAYER2 : PLAYER1;

        if (turn == PLAYER2)
			std::cout<<"PLAYER2 has won\n";
		else
			std::cout<<"PLAYER1 has won\n";
    }
}

bool winDetection(std::vector<std::vector<char>> board){
    	for (int i = 0; i < GRID; i++){
		if (board[i][0] == board[i][1] &&
			board[i][1] == board[i][2] &&
			board[i][0] != ' ')
			return (true);
        else if (board[0][i] == board[1][i] &&
			board[1][i] == board[2][i] &&
			board[0][i] != ' ')
			return (true);
        else if (board[0][0] == board[1][1] &&
            board[1][1] == board[2][2] &&
            board[0][0] != ' ')
            return(true);
        else if (board[0][2] == board[1][1] &&
            board[1][1] == board[2][0] &&
            board[0][2] != ' ')
            return(true);
	}
	return(false);
}

