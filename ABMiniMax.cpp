#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ABMiniMax.h"
#include "Node.h"

AI::AI(Node *root, bool order, int ply, char Mark){
  this->root = root;
  turn = (order) ? true : false;
  mark = Mark;
  if(Mark == 'X'){
    oppMark = 'O';
  }else{
    oppMark = 'X';
  }
  plyMAX = ply;
}

std::vector<std::vector<char>> AI::playMove(std::vector<std::vector<char>> board, int movesTaken){
  Node r = Node(board);
  root = &r;
  GenerateChildren(mark, root);
  int bestMove = -50000;
  std::vector<std::vector<char>> bestPlay;

  for(auto i : root->getChildren()){
    int mo = ABMinimax(i, 0, turn, 50000, -50000);
    //std::cout << mo << std::endl;
    //displayBoard(i->getBoard());
    if(mo > bestMove){
      bestMove = mo;
      bestPlay = i->getBoard();
    }
  }

  if(root->getChildren().size() == 1) {
    bestPlay = root->getChildren().back()->getBoard();
  }


  return bestPlay;
}

int AI::ABMinimax(Node *node, int depth, bool maxPlayer, int ut, int pt){
   /* if(node->getChildren().empty()){
        //std::cout << "empty" << std::endl;
        return Heuristic1(node->getBoard(), maxPlayer);
    }*/

    if(depth != 2) {
        char mark = (maxPlayer) ? 'X' : 'O';
        //std::cout << "call ab\n";
        GenerateChildren(mark, node);

        for(auto i : node->getChildren()){
            int value = ABMinimax(i, depth + 1, !maxPlayer, -pt, -ut);
            int newValue = -value;
            if(newValue > pt) {
                pt = newValue;
            }
            if(pt < ut)
                break;
            else
                return pt;
        }
    } else {
        int value = Heuristic1(node->getBoard(), maxPlayer);
        if(!maxPlayer)
            return -value;
        return value;
    }

    return pt;
}

int AI::Heuristic1(std::vector<std::vector<char>> board, bool currentPlayer){
	int myPossibleWins = findPossibleWins(board, currentPlayer);
	int opponentPlayerWins = findPossibleWins(board, !currentPlayer);
	return myPossibleWins - opponentPlayerWins;
}

int AI::Heuristic2(){
  return 0;
}

int AI::Heuristic3(){
  return 0;
}

int AI::Heuristic4(){
  return 0;
}


void AI::GenerateChildren(char playerMark, Node *curNode){
  char oppMark = (playerMark == 'X') ? 'O' : 'X';
  std::vector<std::vector<char>> b = curNode->getBoard();
  //std::cout << "ply: " << ply << std::endl;
  //displayBoard(b);

  for(int i = 0; i != b.size(); i++){
    for(int j = 0; j != b.size(); j++){
      std::vector<std::vector<char>> childB = b;
      if(b[i][j] == ' '){
        //set the empty space to the players mark
        childB[i][j] = playerMark;
        //create a child node with this new board and add the new child to the current nodes children
        curNode->addChild(childB);
        //displayBoard(childB);
        //GenerateChildren(++ply, oppMark, curNode->getChildren().back());
      }
    }
  }
}

void AI::displayBoard(std::vector<std::vector<char>> board){
    std::cout << "\t\t\t " << (board[0][0]) << " | " << (board[0][1]) << " | " << (board[0][2]) << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t " << (board[1][0]) << " | " << (board[1][1]) << " | " << (board[1][2]) << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t " << (board[2][0]) << " | " << (board[2][1]) << " | " << (board[2][2]) << std::endl;
    std::cout << "\n" << std::endl;
}


void AI::setBoard(std::vector<std::vector<char>> board){
  Node nRoot = Node(board);
  this->root = &nRoot;
}

int AI::findPossibleWins(std::vector<std::vector<char>> board, bool currentPlayer){
	char myPlayerMove = (currentPlayer) ? mark : oppMark;
	int winCount = 0;

    //std::cout << myPlayerMove << std::endl;
    //displayBoard(board);

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
