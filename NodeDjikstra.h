#include "Node.h"
#include <vector>
#include <string>

class NodeDj: public Node {
  public:
    NodeDj(float x, float y, std::string name = ""): Node(x, y, name) {}
    float tnDist();
    void setTnDist(float newTnDist);
    bool visited();
    void setVisited(bool newVisited);
    NodeDj* prev();
    void setPrev(NodeDj* newPrev);
    std::vector<NodeDj*> neighbors();
    void addNeighbor(NodeDj* node);
  private:
    float _tnDist = 99999;
    bool _visited = false;
    NodeDj* _prev = NULL;
    std::vector<NodeDj*> _neighbors;
};
