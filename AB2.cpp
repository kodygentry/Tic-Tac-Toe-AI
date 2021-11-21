#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <bits/stdc++.h>
#include "AB2.h"
#include "Node.h"

AI2::AI2(bool order, int heuristicId) : root(nullptr) {
    turn = order;
    mark = turn ? 'X' : 'O';
    oppMark = turn ? 'O' : 'X';
    algorithmId = heuristicId;
}

std::vector<std::vector<char>> AI2::playMove(std::vector<std::vector<char>> board, int movesTaken) {
    expNodes = std::make_shared<Node>(Node(board));
    root = std::make_shared<Node>(Node(board));
    return ABMinimax(root, 0, turn, 50000, -50000).second;
}

std::pair<int, std::vector<std::vector<char>>> AI2::ABMinimax(std::shared_ptr<Node> node, int depth, bool maxPlayer, int ut, int pt) {
    if(DeepEnough(node->getBoard(), depth, maxPlayer)) {
        int value;
        if(algorithmId == 1)
            value = Heuristic1(node->getBoard(), maxPlayer);
        else if(algorithmId == 2)
            value = Heuristic2(node->getBoard(), maxPlayer);
        else if(algorithmId == 3)
            value = Heuristic3(node->getBoard(), maxPlayer);
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
        else if(algorithmId == 3)
            value = Heuristic3(node->getBoard(), maxPlayer);
        value = (maxPlayer) ? value : -value;
        return std::make_pair(value, node->getBoard());
    }

    std::vector<std::vector<char>> bestBoard;
    std::vector<int> values;
    int cnt = 0;
    for(auto i : node->getChildren()) {
        expNodes->addChild(i->getBoard());
        std::pair<int, std::vector<std::vector<char>>> pairVal = ABMinimax(i, depth + 1, !maxPlayer, -pt, -ut);
        int newValue = -pairVal.first;
        if(newValue > pt) {
            bestBoard = i->getBoard();
            pt = newValue;
        }
        if(pt >= ut){
            return std::make_pair(pt, i->getBoard());
        }
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
    int myAlmostWins = calculateAlmostWins(board, currentPlayer);
    int oppAlmostWins = calculateAlmostWins(board, !currentPlayer);

    return myAlmostWins - oppAlmostWins;
}

int AI2::Heuristic3(std::vector<std::vector<char>> board, bool currentPlayer){
  int me = findMagicWins(board, currentPlayer);
  int opp = findMagicWins(board, !currentPlayer);
  if(currentPlayer){
    return opp - me;
  }
  return me - opp;
}

int AI2::findMagicWins(std::vector<std::vector<char>> board, bool currentPlayer){
  /*
  int myWins = 0;
  std::vector<std::vector<int>> ms = {{2, 7, 6}, {9, 5, 1}, {4, 3, 8}};
  std::vector<int> mySpots;
  std::vector<int> oppSpots;
  std::vector<int> neuSpots;
  char myMark = (currentPlayer) ? 'X' : 'O';
  for(size_t i = 0; i != 3; i++){
    for(size_t j = 0; j != 3; j++){
      if(board[i][j] == myMark){
        mySpots.push_back(ms[i][j]);
      }else if(board[i][j] == ' '){
        neuSpots.push_back(ms[i][j]);
      }else{
        oppSpots.push_back(ms[i][j]);
      }
    }
  }
  for(size_t i = 0; i != mySpots.size(); i++){
    for(size_t j = i + 1; j != mySpots.size(); j++){
      int check = 15 - mySpots[i] - mySpots[j];
      if(check > 0 && check <= 9){
        if(std::find(mySpots.begin(), mySpots.end(), check) != mySpots.end()){
          //we won FUCCKKER YESSS
          return 50000;
        }else if(std::find(neuSpots.begin(), neuSpots.end(), check) != neuSpots.end()){
          //we have a possible win here
          myWins += 2;
        }
      }
    }
  }
  for(size_t i = 0; i != oppSpots.size(); i++){
    for(size_t j = i + 1; j != oppSpots.size(); j++){
      int check = 15 - oppSpots[i] - oppSpots[j];
      if(check > 0 && check <= 9){
        if(std::find(oppSpots.begin(), oppSpots.end(), check) != oppSpots.end()){
          //opponent has won fuck!!!!
          return -50000;
        }else if(std::find(mySpots.begin(), mySpots.end(), check) != mySpots.end()){
          //We wanna block if we don't win
          myWins += 5000;
        }else if(std::find(neuSpots.begin(), neuSpots.end(), check) != neuSpots.end()){
//if the opponent has a possible win that isn't good;
          myWins -= -500;
        }
      }
    }
  }
  for(size_t i = 0; i != neuSpots.size(); i++){
    myWins++;
  }
  return myWins;
  */
  bool myWins = winDetection(board, currentPlayer);
  bool myoppWins = winDetection(board, !currentPlayer);
  if(myWins){
    return 10;
  }else if(myoppWins){
    return -10;
  }else{
    return 0;
  }
}

void AI2::GenerateChildren(char playerMark, std::shared_ptr<Node> curNode){
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

int AI2::calculateAlmostWins(std::vector<std::vector<char>> board, bool currentPlayer) {
    char myPlayerMove = (currentPlayer) ? mark : oppMark;
    int winCount = 0;
    for (int x = 0; x < 3; x++) {
        std::vector<char> moves;
        for(int y = 0; y < 3; y++) {
            moves.push_back(board[x][y]);
        }
        int myMoveCount = count(moves.begin(), moves.end(), myPlayerMove);
        int blankCount = count(moves.begin(), moves.end(), ' ');
        if(myMoveCount == 3) {
            winCount += 3;
        } else if(myMoveCount == 2 && blankCount == 1) {
            winCount += 2;
        } else if(myMoveCount == 1 && blankCount == 2) {
            winCount += 1;
        }
	}

	for(int y = 0; y < 3; y++) {
        std::vector<char> moves;
        for (int x = 0; x < 3; x++) {
            moves.push_back(board[x][y]);
        }
        int myMoveCount = count(moves.begin(), moves.end(), myPlayerMove);
        int blankCount = count(moves.begin(), moves.end(), ' ');
        if(myMoveCount == 3) {
            winCount += 3;
        } else if(myMoveCount == 2 && blankCount == 1) {
            winCount += 2;
        } else if(myMoveCount == 1 && blankCount == 2) {
            winCount += 1;
        }
	}

    std::vector<char> moves;
	if((board[0][0] == ' ' || board[0][0] == myPlayerMove)
		&& (board[1][1] == ' ' || board[1][1] == myPlayerMove)
		&& (board[2][2] == ' ' || board[2][2] == myPlayerMove)) {
		moves.push_back(board[0][0]);
		moves.push_back(board[1][1]);
		moves.push_back(board[2][2]);
	}
	int myMoveCount = count(moves.begin(), moves.end(), myPlayerMove);
    int blankCount = count(moves.begin(), moves.end(), ' ');
    if(myMoveCount == 3) {
        winCount += 3;
    } else if(myMoveCount == 2 && blankCount == 1) {
        winCount += 2;
    } else if(myMoveCount == 1 && blankCount == 2) {
        winCount += 1;
    }

    moves.clear();
	if((board[2][0] == ' ' || board[2][0] == myPlayerMove)
		&& (board[1][1] == ' ' || board[1][1] == myPlayerMove)
		&& (board[0][2] == ' ' || board[0][2] == myPlayerMove)) {
		moves.push_back(board[2][0]);
		moves.push_back(board[1][1]);
		moves.push_back(board[0][2]);
	}
	myMoveCount = count(moves.begin(), moves.end(), myPlayerMove);
    blankCount = count(moves.begin(), moves.end(), ' ');
    if(myMoveCount == 3) {
        winCount += 3;
    } else if(myMoveCount == 2 && blankCount == 1) {
        winCount += 2;
    } else if(myMoveCount == 1 && blankCount == 2) {
        winCount += 1;
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

void AI2::displayNode(std::shared_ptr<Node> node){
  auto board = node->getBoard();
    std::cout << "\t\t\t " << (board[0][0]) << " | " << (board[0][1]) << " | " << (board[0][2]) << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t " << (board[1][0]) << " | " << (board[1][1]) << " | " << (board[1][2]) << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t " << (board[2][0]) << " | " << (board[2][1]) << " | " << (board[2][2]) << std::endl;
    std::cout << "\n" << std::endl;
}

std::shared_ptr<Node> AI2::getExpNodes(){
  return expNodes;
}
