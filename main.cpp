#include <iostream>
#include <string>
#include "AI.h"
#include "Node.h"
#include <memory>
#include <vector>
#include <algorithm>
#include <chrono>


const int PLAYER1 = 1, PLAYER2 = 2;
const char PLAYER1MOVE = 'X', PLAYER2MOVE = 'O';
const int GRID = 3; // value of size of board (ex. GRID 3 = 3x3. GRID 4 = 4x4)


// inititalize
void header();
void displayBoardLayout();
void displayBoard(std::vector<std::vector<char>> board);

// game logic
void startGame(int, bool);
bool winDetection(std::vector<std::vector<char>> board);
void displayPath(std::shared_ptr<Node>);
void tabulateNodes(std::shared_ptr<Node>);

int main(int argc, char **argv){
	bool showSteps = false;
	if(argc > 1) {
		if(strcmp(argv[1], "-d") == 0) {
			showSteps = true;
		}
	}
	header();
	startGame(PLAYER1, showSteps);
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

void startGame(int turn, bool showSteps) {
	int aiMaxId = 1;
	std::cout << "Enter evaluation function for Max (1-4): ";
	std::cin >> aiMaxId;
	int aiMinId = 1;
	std::cout << "Enter evaluation function for Min (1-4): ";
	std::cin >> aiMinId;
	
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<char>> board(GRID, std::vector<char>(GRID, ' '));
    int index = 0; // for depth index

    AI aiMax(true, aiMaxId); //last number is heuristic id
    AI aiMin(false, aiMinId); //last number is heuristic id

    int maxNodes = 0;
    int minNodes = 0;

    while (winDetection(board) == false && index != GRID * GRID){
        if(turn == PLAYER1) {
            board = aiMax.playMove(board);

            std::cout << "X's move" << std::endl;
            displayBoard(board);
            maxNodes += aiMax.getExpNodes()->getChildren().size();

			if(showSteps) {
				std::cout << "Displaying Explored Max Expanded Nodes\n";
				displayPath(aiMax.getExpNodes());
				std::cout << "Finished Exploring Max Expanded Nodes\n";
			}

            turn = PLAYER2;
        } else {
            std::cout << "O's move" << std::endl;
            board = aiMin.playMove(board);
            displayBoard(board);
            minNodes += aiMin.getExpNodes()->getChildren().size();

            if(showSteps) {
				std::cout << "Displaying Explored Min Expanded Nodes\n";
				displayPath(aiMin.getExpNodes());
				std::cout << "Finished Exploring Min Expanded Nodes\n";
			}

            turn = PLAYER1;
        }
        index++;
    }

    std::cout << "\n-----------------------------------------------------------\n";
    if (winDetection(board) == false) {
        std::cout << "Draw\n";
    } else {
        turn = (turn == PLAYER1) ? PLAYER2 : PLAYER1;

        if (turn == PLAYER2)
			std::cout<< "O has won\n";
		else
			std::cout<< "X has won\n";
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Execution time: " << duration.count() << " milliseconds.\n";
    std::cout << "Total nodes expanded and explored: " << maxNodes + minNodes << "\n";
    std::cout << "\n-----------------------------------------------------------\n";
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

void displayPath(std::shared_ptr<Node> expNode){
  displayBoard(expNode->getBoard());
  for(auto i : expNode->getChildren()){
    std::cout << "Expanded Node\n";
    displayBoard(i->getBoard());
    std::cout << "Moving on to next child\n";
  }
  std::cout << "Exiting displayPath()\n";
}

void tabulateNodes(std::shared_ptr<Node> expNode){
  std::cout << "Number of Nodes expaned and explored: " << expNode->getChildren().size() << "\n";
}
