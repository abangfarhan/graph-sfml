#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

class Node
{
  public:
    Node();
    Node(float x, float y);
    Node(std::string name, float x, float y);
    float x();
    float y();
    std::string name();
    void setX(float x);
    void setY(float y);
    void setName(std::string name);
    void addNeighbor(Node* node);
    std::vector<Node*> neighbors();
  private:
    float _x;
    float _y;
    std::string _name;
    std::vector<Node*> _neighbors;
};

#endif
