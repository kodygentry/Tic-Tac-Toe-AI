#ifndef NODE
#define NODE
#include <vector>

class Node{
  private:
    std::vector<Node *> children;
    std::vector<std::vector<char>> board;
  public:
    Node(std::vector<std::vector<char>>);
    void addChild(std::vector<std::vector<char>>);
    Node * getChild(int child);
    std::vector<std::vector<char>> getBoard();
    std::vector<Node *> getChildren();
};

#endif
