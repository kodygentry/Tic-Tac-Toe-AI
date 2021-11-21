#ifndef NODE
#define NODE
#include <vector>
#include <memory>

class Node{
  private:
    std::vector<std::shared_ptr<Node>> children;
    std::vector<std::vector<char>> board;
    std::shared_ptr<Node> parent;
  public:
    Node(std::vector<std::vector<char>>);
    void addChild(std::vector<std::vector<char>>);
    std::shared_ptr<Node> getChild(int child);
    std::vector<std::vector<char>> getBoard();
    std::vector<std::shared_ptr<Node>> getChildren();
    void setBoard(std::vector<std::vector<char>>);
};

#endif
