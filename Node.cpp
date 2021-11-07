#include "Node.h"
#include <vector>

Node::Node(std::vector<std::vector<char>> board){
  this->board = board;
}

void Node::addChild(std::vector<std::vector<char>> child){
  Node *sonPtr = new Node(child);
  children.push_back(sonPtr);
}

Node* Node::getChild(int child){
  if(child >= children.size()){
    return nullptr;
  }else{
    return children[child];
  }
}

std::vector<std::vector<char>> Node::getBoard(){
  return this->board;
}

std::vector<Node *> Node::getChildren(){
  return children;
}
