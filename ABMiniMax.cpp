#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ABMiniMax.h"
#include "Node.h"

AI::AI(Node *root, bool order, int ply, char Mark, int heuristicId){
  this->root = root;
  turn = (order) ? true : false;
  mark = Mark;
  if(Mark == 'X'){
    oppMark = 'O';
  }else{
    oppMark = 'X';
  }
  plyMAX = ply;
  algorithId = heuristicId;
}

std::vector<std::vector<char>> AI::playMove(std::vector<std::vector<char>> board, int movesTaken){
  std::vector<std::vector<char>> test = {{'O', ' ', 'X'}, {'O', ' ', 'X'}, {' ', ' ', ' '}};
  Node r = Node(board);
  Node t = Node(test);
  root = &r;
  Node *te = &t;
  int bestMove = -50000;
  GenerateChildren(mark, root);
  std::vector<std::vector<char>> bestPlay;

  for(auto i : root->getChildren()){
    int mo = ABMinimax(i, 0, !turn, bestMove, -bestMove);
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

    if(DeepEnough(node->getBoard(), depth, maxPlayer)) {
        char mark = (maxPlayer) ? 'X' : 'O';

        GenerateChildren(mark, node);

        for(auto i : node->getChildren()){
            int value = ABMinimax(i, depth + 1, !maxPlayer, -pt, -ut);
            int newValue = -value;
            if(newValue > pt) {
                pt = newValue;
            }
            if(pt >= ut)
                return pt;
            else
                break;
        }
    } else {
        int value;
        if(algorithId == 1)
            value = Heuristic1(node->getBoard(), maxPlayer);
        else if(algorithId == 2)
            value = Heuristic2(node->getBoard(), maxPlayer);
        else if(algorithId == 3)
            value = Heuristic3(node, maxPlayer);

        if(!maxPlayer)
            return -value;
        return value;
    }

    return pt;
}

bool AI::DeepEnough(std::vector<std::vector<char>> board, int currentDepth, bool currentPlayer) {
    bool myPlayerWin = winDetection(board, currentPlayer);
    bool oppPlayerWin = winDetection(board, !currentPlayer);
    if(myPlayerWin || oppPlayerWin)
        return true;

    if(currentDepth == 5) {
        return true;
    } else {
      int cntFreeSpaces = 0;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == ' ') {
                  cntFreeSpaces++;
                }
            }
        }
        if(cntFreeSpaces == 1 && !myPlayerWin && !oppPlayerWin){
          return true;
        }
    }
    return false;
}

int AI::Heuristic1(std::vector<std::vector<char>> board, bool currentPlayer){
	int myPossibleWins = findPossibleWins(board, currentPlayer);
	int opponentPlayerWins = findPossibleWins(board, !currentPlayer);
	return myPossibleWins - opponentPlayerWins;
}

int AI::Heuristic2(std::vector<std::vector<char>> board, bool currentPlayer){
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

int AI::Heuristic3(Node *node, bool currPlayer){
  int myPWins = findMagicWins(node, currPlayer);
  int oPWins = findMagicWins(node, !currPlayer);
  return myPWins - oPWins;
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

int AI::findMagicWins(Node *node, bool currPlayer){
  std::vector<std::vector<int>> magicSquare = {{8, 3, 4}, {1,5,9}, {6,7,2}};
  int possibleWins = 0;
  std::vector<int> ownPositions;
  std::vector<int> neutralPositions;
  std::vector<int> oppPositions;
  std::vector<std::vector<char>> curBoard = node->getBoard();
  char playerMark = (currPlayer) ? mark : oppMark;
  char oppMark = (currPlayer) ? oppMark : mark;
  //find the positions we own, add their magic number to the list
  for(int i = 0; i != 3; i++){
    for(int j = 0; j != 3; j++){
      if(curBoard[i][j] == playerMark){
        ownPositions.push_back(magicSquare[i][j]);
      }else if(curBoard[i][j] == oppMark){
        oppPositions.push_back(magicSquare[i][j]);
      }else{
        neutralPositions.push_back(magicSquare[i][j]);
      }
    }
  }
  //calculate the positions for a possible win given the positions I own
  std::vector<int> explored;
  for(int i = 0; i != ownPositions.size(); i++){
    for(int j = i+1; j != ownPositions.size(); j++){
      int check = 15 - ownPositions[i] - ownPositions[j];
      //check if the numbers are collinear
      if(check > 0 && check <= 9){
        //check if the number is owned by the oppent
        if(std::find(oppPositions.begin(), oppPositions.end(), check) == oppPositions.end()){
          if(std::find(ownPositions.begin(), ownPositions.end(), check) != ownPositions.end()){
            return 300;
          }
          possibleWins++;
          explored.push_back(check);
        }
      }
    }
  }

  //check the positions owned by neither player
  for(int i = 0; i != neutralPositions.size(); i++){
    for(int j = i + 1; j != neutralPositions.size(); j++){
      int check = 15 - neutralPositions[i] - neutralPositions[j];
      if(check > 0 && check <= 9){
        if(std::find(oppPositions.begin(), oppPositions.end(), check) == oppPositions.end()){
          possibleWins--;
        }else if(std::find(explored.begin(), explored.end(), check) == explored.end()){
          explored.push_back(check);
          possibleWins++;
        }
      }
    }
  }
  return possibleWins;
}

bool AI::winDetection(std::vector<std::vector<char>> board, bool currentPlayer){
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

void AI::printBoard(Node *node){
  auto board = node->getBoard();
    std::cout << "\t\t\t " << (board[0][0]) << " | " << (board[0][1]) << " | " << (board[0][2]) << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t " << (board[1][0]) << " | " << (board[1][1]) << " | " << (board[1][2]) << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t " << (board[2][0]) << " | " << (board[2][1]) << " | " << (board[2][2]) << std::endl;
}
