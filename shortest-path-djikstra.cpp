#include <iostream>
#include "NodeDjikstra.h"
#include <SFML/Graphics.hpp>
#include "graphHelper.h"

#define PI 3.14159265

void showPath(NodeDj* dest);

int main()
{
    const int width = 800;
    const int height = 600;

    int n_nodes = 10;
    NodeDj* nodeList[n_nodes];
    fillGraph<NodeDj>(nodeList, n_nodes, width, height, 1, 5);

    bool is_solving = true;
    NodeDj* start = nodeList[0];
    NodeDj* dest = nodeList[n_nodes - 1];
    NodeDj* current = start;
    start->setTnDist(0);

    // mark beginning and ending node
    int radius = 5;
    sf::CircleShape startCircle;
    startCircle.setPosition(start->x() - radius, start->y() - radius);
    startCircle.setRadius(radius);
    startCircle.setFillColor(sf::Color::Red);

    sf::CircleShape endCircle;
    endCircle.setPosition(dest->x() - radius, dest->y() - radius);
    endCircle.setRadius(radius);
    endCircle.setFillColor(sf::Color::Red);

    sf::RenderWindow window(sf::VideoMode(width, height), "Djikstra");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        for (int i = 0; i < n_nodes; ++i)
        {
            // line connecting all nodes
            for (NodeDj* neighbor: nodeList[i]->neighbors())
            {
                sf::RectangleShape line = Line(nodeList[i]->x(), nodeList[i]->y(), neighbor->x(), neighbor->y());
                line.setFillColor(sf::Color(200, 200, 200));
                window.draw(line);
            }

            // line connecting visited nodes
            if (nodeList[i]->prev() != NULL)
            {
                NodeDj* prev = nodeList[i]->prev();
                sf::RectangleShape line = Line(nodeList[i]->x(), nodeList[i]->y(), prev->x(), prev->y(), 2);
                line.setFillColor(sf::Color(100, 100, 100));
                window.draw(line);
            }
        }

        if (is_solving)
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

            // if destination has been marked 'visited', or facing a dead-end
            // if (dest->visited() || current == NULL)
            if (current == NULL)
                is_solving = false;
        }
        else
        {
            bool all_connected = true;
            for (int i = 1; i < n_nodes; ++i)
            {
                if (nodeList[i]->prev() == NULL)
                    all_connected = false;
            }
            if (!all_connected) graphInfo(nodeList, n_nodes);
        }

        if (dest->prev() != NULL)
        {
            NodeDj* node = dest;
            NodeDj* prev;
            while (node->prev() != NULL)
            {
                prev = node->prev();
                sf::RectangleShape line = Line(node->x(), node->y(), prev->x(), prev->y(), 3);
                line.setFillColor(sf::Color::Green);
                window.draw(line);
                node = prev;
            }
        }

        window.draw(startCircle);
        window.draw(endCircle);
        window.display();
        sf::sleep(sf::milliseconds(100));
    }
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
