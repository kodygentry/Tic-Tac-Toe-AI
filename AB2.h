#include "Node.h"
#include <memory>
#include <vector>
#include <deque>

class AI2 {
  public:
     AI2(bool, int);
     std::vector<std::vector<char>> playMove(std::vector<std::vector<char>>);
     std::shared_ptr<Node> getExpNodes();

  private:
     std::pair<int, std::vector<std::vector<char>>> ABMinimax(std::shared_ptr<Node>, int, bool, int, int);
     bool DeepEnough(std::vector<std::vector<char>>, int, bool);
     int Heuristic1(std::vector<std::vector<char>>, bool);
     int Heuristic2(std::vector<std::vector<char>>, bool);
     int Heuristic3(std::vector<std::vector<char>>, bool);
     int Heuristic4(std::vector<std::vector<char>>, bool);
     int findPossibleWins(std::vector<std::vector<char>>, bool);
     int calculateAlmostWins(std::vector<std::vector<char>>, bool);
     int findMagicWins(std::vector<std::vector<char>>, bool);
     int openLengths(std::vector<std::vector<char>>, bool);
     bool winDetection(std::vector<std::vector<char>>, bool);
     void GenerateChildren(char, std::shared_ptr<Node>);
     void displayBoard(std::vector<std::vector<char>>);
     void displayNode(std::shared_ptr<Node>);

     std::shared_ptr<Node> root;
     bool turn;
     char mark;
     char oppMark;
     int algorithmId;
     std::shared_ptr<Node> expNodes;
};
