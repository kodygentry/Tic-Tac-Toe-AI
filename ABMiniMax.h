#ifndef ABMINIMAX
#define ABMINIMAX
#include "Node.h"

class AI{
   // ai has a tree of nodes
  public:
     // ai has ABMinimax function
     AI(Node *, bool, int, char);
     // ai can generate children given the current board, the root node will be the current state of the board, the first ply will be the moves the ai can make and the 2nd ply will be the moves the player can make
     void GenerateChildren(int, char, Node *);
     // nodes will be of type char double array
     std::vector<std::vector<char>> mkMove();
     std::vector<std::vector<char>> playMove(std::vector<std::vector<char>>);
     void setBoard(std::vector<std::vector<char>>);
     void displayBoard(std::vector<std::vector<char>>);
  private:
     int ABMinimax(Node *, bool, int, int);
     // ai has Heuristic evaluation functions
     int Heuristic1(std::vector<std::vector<char>>, bool);
     int Heuristic2();
     int Heuristic3();
     int Heuristic4();
     int findPossibleWins(std::vector<std::vector<char>>, bool);
     Node *root;
     bool turn;
     int plyMAX, alpha, beta;
     char mark;
     char oppMark;
};

#endif
