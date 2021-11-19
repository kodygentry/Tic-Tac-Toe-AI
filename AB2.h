#include "Node.h"

class AI2 {
  public:
     AI2(Node *, bool, int);
     std::vector<std::vector<char>> playMove(std::vector<std::vector<char>>, int);

  private:
     std::pair<int, std::vector<std::vector<char>>> ABMinimax(Node *, int, bool, int, int);
     bool DeepEnough(std::vector<std::vector<char>>, int, bool);
     int Heuristic1(std::vector<std::vector<char>>, bool);
     int Heuristic2(std::vector<std::vector<char>>, bool);
     int findPossibleWins(std::vector<std::vector<char>>, bool);
     int calculateAlmostWins(std::vector<std::vector<char>>, bool);
     bool winDetection(std::vector<std::vector<char>>, bool);
     void GenerateChildren(char, Node *);
     void displayBoard(std::vector<std::vector<char>>);

     Node *root;
     bool turn;
     char mark;
     char oppMark;
     int algorithmId;
};
