#ifndef ABMINIMAX
#define ABMINIMAX
#include "Node.h"

class AI{
   // ai has a tree of nodes
  public:
     // ai has ABMinimax function
     AI(Node *, bool, int, char, int);
     // ai can generate children given the current board, the root node will be the current state of the board, the first ply will be the moves the ai can make and the 2nd ply will be the moves the player can make
     void GenerateChildren(char, Node *);
     // nodes will be of type char double array
     std::vector<std::vector<char>> playMove(std::vector<std::vector<char>>, int);
     void setBoard(std::vector<std::vector<char>>);
     void displayBoard(std::vector<std::vector<char>>);
  private:
     int ABMinimax(Node *, int, bool, int, int);
     // ai has Heuristic evaluation functions
     int Heuristic1(std::vector<std::vector<char>>, bool);
     int Heuristic2(std::vector<std::vector<char>>, bool);
     int Heuristic3();
     int Heuristic4(std::vector<std::vector<char>>, bool);
     bool DeepEnough(std::vector<std::vector<char>>, int, bool);
     int findPossibleWins(std::vector<std::vector<char>>, bool);
     int openLengths(std::vector<std::vector<char>>, bool);
     bool winDetection(std::vector<std::vector<char>>, bool);
     int algorithId;
     Node *root;
     bool turn;
     int plyMAX, alpha, beta;
     char mark;
     char oppMark;
};

#endif
