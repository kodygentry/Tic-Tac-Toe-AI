#include "AI.h"
#include <memory>
#include <vector>

Node::Node(std::vector<std::vector<char>> board){
  this->parent = nullptr;
  this->board = board;
}

void Node::addChild(std::vector<std::vector<char>> child){
  std::shared_ptr<Node> sonPtr = std::make_shared<Node>(Node(child)) ;
  children.push_back(sonPtr);
}

std::shared_ptr<Node> Node::getChild(int child){
  if(child >= children.size()){
    return nullptr;
  }else{
    return children[child];
  }
}

std::vector<std::vector<char>> Node::getBoard(){
  return this->board;
}

std::vector<std::shared_ptr<Node>> Node::getChildren(){
  return children;
}
