#include "Node.h"

Node::Node() { setName(""); setX(0); setY(0); }
Node::Node(float x, float y) {
    setName("");
    setX(x);
    setY(y);
}
Node::Node(std::string name, float x, float y) {
    setName(name);
    setX(x);
    setY(y);
}

float Node::x() { return _x; }
float Node::y() { return _y; }
std::string Node::name() { return _name; }
void Node::setX(float x) { _x = x; }
void Node::setY(float y) { _y = y; }
void Node::setName(std::string name) { _name = name; }
void Node::addNeighbor(Node* node)
{
    // Add neighbor node to this->_neighbors if not exist,
    // and add this to the neighbor node->_neighbors
    for (Node* neighbor: _neighbors)
        if (neighbor == node) return;
    _neighbors.push_back(node);
    node->addNeighbor(this);
}

std::vector<Node*> Node::neighbors() { return _neighbors; }
