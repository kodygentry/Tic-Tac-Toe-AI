#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include "AB2.h"
#include "Node.h"

AI2::AI2(Node *root, bool order, int heuristicId){
    this->root = root;
    turn = order;
    mark = turn ? 'X' : 'O';
    oppMark = turn ? 'O' : 'X';
    algorithmId = heuristicId;
}

std::vector<std::vector<char>> AI2::playMove(std::vector<std::vector<char>> board, int movesTaken) {
    Node r = Node(board);
    root = &r;

    return ABMinimax(root, 0, turn, 50000, -50000).second;
}

std::pair<int, std::vector<std::vector<char>>> AI2::ABMinimax(Node *node, int depth, bool maxPlayer, int ut, int pt) {
    if(DeepEnough(node->getBoard(), depth, maxPlayer)) {
        int value;
        if(algorithmId == 1)
            value = Heuristic1(node->getBoard(), maxPlayer);
        else if(algorithmId == 2)
            value = Heuristic2(node->getBoard(), maxPlayer);

        value = (maxPlayer) ? value : -value;
        return std::make_pair(value, node->getBoard());
    }

    char currMark = (maxPlayer) ? 'X' : 'O';
    GenerateChildren(currMark, node);
    if(node->getChildren().size() == 0) {
        int value;
        if(algorithmId == 1)
            value = Heuristic1(node->getBoard(), maxPlayer);
        else if(algorithmId == 2)
            value = Heuristic2(node->getBoard(), maxPlayer);

        value = (maxPlayer) ? value : -value;
        return std::make_pair(value, node->getBoard());
    }

    std::vector<std::vector<char>> bestBoard;
    for(auto i : node->getChildren()) {
        std::pair<int, std::vector<std::vector<char>>> pairVal = ABMinimax(i, depth + 1, !maxPlayer, -pt, -ut);
        int newValue = -pairVal.first;
        if(newValue > pt) {
            bestBoard = i->getBoard();
            pt = newValue;
        }
        if(pt >= ut)
            return std::make_pair(pt, i->getBoard());
    }

    return std::make_pair(pt, bestBoard);
}

bool AI2::DeepEnough(std::vector<std::vector<char>> board, int currentDepth, bool currentPlayer) {
    bool myPlayerWin = winDetection(board, currentPlayer);
    bool oppPlayerWin = winDetection(board, !currentPlayer);
    if(myPlayerWin || oppPlayerWin)
        return true;

    if(currentDepth == 2) {
        return true;
    } else {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == ' ') {
                    return false;
                }
            }
        }
    }

    return true;
}

int AI2::Heuristic1(std::vector<std::vector<char>> board, bool currentPlayer){
	int myPossibleWins = findPossibleWins(board, currentPlayer);
	int opponentPlayerWins = findPossibleWins(board, !currentPlayer);
	return myPossibleWins - opponentPlayerWins;
}

int AI2::Heuristic2(std::vector<std::vector<char>> board, bool currentPlayer){
    char myPlayerMove = (currentPlayer) ? mark : oppMark;
    char opponentMark = (currentPlayer) ? oppMark : mark;

    for (int i = 0; i < 3; i++){
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if(board[i][0] == myPlayerMove)
                return 1;
            else if(board[i][0] == opponentMark)
                return -1;
        } else if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if(board[0][i] == myPlayerMove)
                return 1;
            else if(board[0][i] == opponentMark)
                return -1;
        } else if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if(board[0][0] == myPlayerMove)
                return 1;
            else if(board[0][0] == opponentMark)
                return -1;
        } else if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if(board[0][2] == myPlayerMove)
                return 1;
            else if(board[0][2] == opponentMark)
                return -1;
        }
	}
    return 0;
}

void AI2::GenerateChildren(char playerMark, Node *curNode){
    char oppMark = (playerMark == 'X') ? 'O' : 'X';
    std::vector<std::vector<char>> b = curNode->getBoard();

    for(int i = 0; i != b.size(); i++) {
        for(int j = 0; j != b.size(); j++) {
            std::vector<std::vector<char>> childB = b;
            if(b[i][j] == ' ') {
                childB[i][j] = playerMark;
                curNode->addChild(childB);
            }
        }
    }
}

void AI2::displayBoard(std::vector<std::vector<char>> board){
    std::cout << "\t\t\t " << (board[0][0]) << " | " << (board[0][1]) << " | " << (board[0][2]) << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t " << (board[1][0]) << " | " << (board[1][1]) << " | " << (board[1][2]) << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t " << (board[2][0]) << " | " << (board[2][1]) << " | " << (board[2][2]) << std::endl;
    std::cout << "\n" << std::endl;
}

int AI2::findPossibleWins(std::vector<std::vector<char>> board, bool currentPlayer){
	char myPlayerMove = (currentPlayer) ? mark : oppMark;
	int winCount = 0;


	// Check # of horizontal possible wins
	for(int x = 0; x < 3; x++) {
		int horizontalCount = 0;
		for(int y = 0; y < 3; y++) {
			if(board[x][y] == ' ' || board[x][y] == myPlayerMove) {
				horizontalCount++;
			}
		}

		if(horizontalCount == 3) {
			winCount++;
		}
	}

	// Check # of vertical possible wins
	for(int y = 0; y < 3; y++) {
		int verticalCount = 0;
		for(int x = 0; x < 3; x++) {
			if(board[x][y] == ' ' || board[x][y] == myPlayerMove) {
				verticalCount++;
			}
		}

		if(verticalCount == 3) {
			winCount++;
		}
	}

	// Check # of diagonal possible wins
	if((board[0][0] == ' ' || board[0][0] == myPlayerMove)
		&& (board[1][1] == ' ' || board[1][1] == myPlayerMove)
		&& (board[2][2] == ' ' || board[2][2] == myPlayerMove)) {
		winCount++;
	}

	if((board[2][0] == ' ' || board[2][0] == myPlayerMove)
		&& (board[1][1] == ' ' || board[1][1] == myPlayerMove)
		&& (board[0][2] == ' ' || board[0][2] == myPlayerMove)) {
		winCount++;
	}

	return winCount;
}

bool AI2::winDetection(std::vector<std::vector<char>> board, bool currentPlayer){
    char myPlayerMove = (currentPlayer) ? mark : oppMark;

    for (int i = 0; i < 3; i++){
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] == myPlayerMove) {
            return true;
        } else if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] == myPlayerMove) {
            return true;
        } else if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == myPlayerMove) {
            return true;
        } else if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == myPlayerMove) {
            return true;
        }
	}
	return (false);
}
