#include <iostream>
#include "NodeDjikstra.h"

void showPath(NodeDj* dest);

int main()
{
    int n_nodes = 4;
    NodeDj* nodeList[n_nodes] = {
        new NodeDj(10, 300, "A"),
        new NodeDj(50, 100, "B"),
        new NodeDj(50, 500, "C"),
        new NodeDj(200, 400, "D")
    };
    nodeList[0]->addNeighbor(nodeList[1]);
    nodeList[0]->addNeighbor(nodeList[2]);
    nodeList[1]->addNeighbor(nodeList[2]);
    nodeList[1]->addNeighbor(nodeList[3]);
    nodeList[2]->addNeighbor(nodeList[3]);

    NodeDj* start = nodeList[0];
    NodeDj* dest = nodeList[3];
    NodeDj* current = start;

    start->setTnDist(0);

    while (true)
    {
        NodeDj* closestNeighbor = NULL;
        for (NodeDj* neighbor: current->neighbors())
        {
            if (neighbor->visited()) continue;
            float currentToNeighborDist = current->distance(neighbor);
            float newNeighborTentativeDist = currentToNeighborDist + current->tnDist();
            if (newNeighborTentativeDist < neighbor->tnDist())
            {
                neighbor->setTnDist(newNeighborTentativeDist);
                neighbor->setPrev(current);
            }
            if (closestNeighbor == NULL || neighbor->tnDist() < closestNeighbor->tnDist())
                closestNeighbor = neighbor;
        }
        current->setVisited(true);
        current = closestNeighbor;
        if (dest->visited()) break;
    }
    showPath(dest);
}

void showPath(NodeDj* dest)
{
    /* Utility function to trace the node path.
     * Use a recursive implementation.
     */
    if (dest == NULL)
    {
        std::cout << "START" << std::endl;
        return;
    }
    std::cout << dest->name() << " <- ";
    showPath(dest->prev());
}
