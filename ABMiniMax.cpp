#include "ABMiniMax.h"
#include "Node.h"
#include <vector>
#include <algorithm>

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

int AI::ABMinimax(Node *node, bool maxPlayer, int a, int b){
  if(node -> getChildren().empty()){
    //return heuristic function
  }
  if(maxPlayer){
    int bestVal = -500;
    for(auto i : node->getChildren()){
      int value = ABMinimax(i, false, a, b);
      bestVal = std::max(bestVal, value);
      a = std::max(alpha, bestVal);
      if(b <= a){
        break;
      }
    }
    return bestVal;
  }else{
    int bestVal = 500;
    for(auto i : node->getChildren()){
      int value = ABMinimax(i, true, a, b);
      bestVal = std::min(bestVal, value);
      b = std::min(b, bestVal);
      if(b <= a){
        break;
      }
    }
    return bestVal;
  }
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


void AI::GenerateChildren(int ply, bool curTurn, Node *curNode){
  std::vector<std::vector<char>> b = curNode->getBoard();
  for(int i = 0; i != b.size(); i++){
    for(int j = 0; j != b.size(); j++){
      std::vector<std::vector<char>> childB = b;
      if(b[i][j] == ' '){
        //set the empty space to the players mark
        if(curTurn){
          //set space to players mark
          childB[i][j] = mark;
        }else{
          //set mark to opposing player
          childB[i][j] = oppMark;
        }
        //create a child node with this new board and add the new child to the current nodes children
        curNode->addChild(childB);
        //recurse and alternate moves
        GenerateChildren(ply++, !curTurn, curNode->getChildren().back());
      }
    }
  }
}

std::vector<std::vector<char>> AI::mkMove(){
  return root->getBoard();
}

void AI::setBoard(std::vector<std::vector<char>> board){
  Node nRoot = Node(board);
  this->root = &nRoot;
}

int AI::findPossibleWins(std::vector<std::vector<char>> board, bool currentPlayer){
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
