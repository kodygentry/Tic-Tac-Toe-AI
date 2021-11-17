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

    if(DeepEnough(node->getBoard(), depth, maxPlayer)) {
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
        int value;
        if(algorithId == 1)
            value = Heuristic1(node->getBoard(), maxPlayer);
        else if(algorithId == 2)
            value = Heuristic2(node->getBoard(), maxPlayer);


        else if(algorithId == 4)
            value = Heuristic4(node->getBoard(), maxPlayer);

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

int AI::Heuristic3(){
  return 0;
}

int AI::Heuristic4(std::vector<std::vector<char>> board, bool currentPlayer){
  // eval functions that returns if currentPlayer position is good/bad based on open board lengths
  // priority is open lengths and middle position after lengths checked
  int myOpen = openLengths(board, currentPlayer);
  int opOpen = openLengths(board, currentPlayer);
  return myOpen - opOpen;
  // resource - Charles R. Dyer, U of Wisconsin-Madison - https://www.csee.umbc.edu/courses/undergraduate/471/spring19/01/notes/07_games/07a.pdf
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

int AI::openLengths(std::vector<std::vector<char>> board, bool currentPlayer){
  char playerMark = (currentPlayer) ? mark : oppMark;
  char oppMark = (currentPlayer) ? oppMark : mark;

  for(int i = 0; i < 3; i++){
    // check rows
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] == ' ') return 10;              // check if length is clear, return good pos
    else if (board[i][0] == playerMark || board[i][1] == playerMark || board[i][2] == playerMark) return 10;   // if not, check if my player is on length, return good pos
    else if (board[i][0] == oppMark || board[i][1] == oppMark || board[i][2] == oppMark) return -10;          // if not, check if opp player is on length, return bad poss

    // check columns
    if (board[0][i] == board[1][i] || board[1][i] == board[2][i] || board[0][i] == ' ') return 10;            // check if length is clear, return good pos
    else if (board[0][i] == playerMark || board[1][i] == playerMark || board[2][i] == playerMark) return 10; // if not, check if my player is on length, return good pos
    else if (board[i][0] == oppMark || board[i][1] == oppMark || board[i][2] == oppMark) return -10;        // if not, check if opp player is on length, return bad poss

    // check diagnals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == ' ') return 10;            // check if length is clear, return good pos
    else if (board[0][0] == playerMark || board[1][1] == playerMark || board[2][2] == playerMark) return 10; // if not, check if my player is on length, return good pos
    else if (board[0][0] == oppMark || board[1][1] == oppMark || board[2][2] == oppMark) return -10;        // if not, check if opp player is on length, return bad poss

    if (board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[2][0] == ' ') return 10;            // check if length is clear, return good pos
    else if (board[2][0] == playerMark || board[1][1] == playerMark || board[0][2] == playerMark) return 10; // if not, check if my player is on length, return good pos
    else if (board[2][0] == oppMark || board[1][1] == oppMark || board[0][2] == oppMark) return -10;        // if not, check if opp player is on length, return bad poss
    

    // middle priority check after lengths (applies only for first move)
    if(board[1][1] == ' ' || board[1][1] == playerMark) return 10;
    else if (board[1][1] == oppMark) return -10;
  }
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
