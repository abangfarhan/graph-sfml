#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "NodeDjikstra.h"
#include "graphHelper.h"

int main(int argc, char* argv[])
{
    bool complete_traversal = true;

    const int width = 800;
    const int height = 600;

    int n_nodes = 30;
    if (argc == 2)
    {
        std::stringstream ss;
        ss << argv[1];
        ss >> n_nodes;
    }
    NodeDj* nodeList[n_nodes];
    fillGraph<NodeDj>(nodeList, n_nodes, width, height, 1, std::min(3, n_nodes));

    bool is_solving = true;
    NodeDj* start = nodeList[0];
    NodeDj* dest = nodeList[n_nodes - 1];
    NodeDj* current = start;
    start->setTnDist(0);

    // mark beginning and ending node
    const int radius = 5;
    sf::CircleShape startMarker;
    startMarker.setPosition(start->x() - radius, start->y() - radius);
    startMarker.setRadius(radius);
    startMarker.setFillColor(sf::Color::Blue);

    sf::CircleShape endMarker;
    endMarker.setPosition(dest->x() - radius, dest->y() - radius);
    endMarker.setRadius(radius);
    endMarker.setFillColor(sf::Color::Red);

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

        // line connecting all nodes
        for (int i = 0; i < n_nodes; ++i)
        {
            for (NodeDj* neighbor: nodeList[i]->neighbors())
            {
                sf::RectangleShape line = Line(nodeList[i]->x(), nodeList[i]->y(), neighbor->x(), neighbor->y());
                line.setFillColor(sf::Color(220, 220, 220));
                window.draw(line);
            }
        }

        // Line connecting visited nodes
        // Why separate loop with the above? To avoid lines overlapping.
        for (int i = 0; i < n_nodes; ++i)
        {
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
            }
            current->setVisited(true);

            // find unvisited nodes with the smallest tnDist
            NodeDj* closestNode = NULL;
            for (int i = 0; i < n_nodes; ++i)
            {
                if (nodeList[i]->visited()) continue;
                if (closestNode == NULL || nodeList[i]->tnDist() < closestNode->tnDist())
                    closestNode = nodeList[i];
            }
            current = closestNode;

            if (complete_traversal && (closestNode == NULL || closestNode->tnDist() == large_number))
            {
                is_solving = false;
                if (closestNode == NULL)
                    std::cout << "Shortest path to every node discovered!" << std::endl;
                else
                    std::cout << "Found no way to visit unvisited nodes" << std::endl;
            }
            else if (!complete_traversal && dest->visited())
            {
                is_solving = false;
                std::cout << "Shortest path to destination discovered!" << std::endl;
            }
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

        window.draw(startMarker);
        window.draw(endMarker);
        window.display();
        sf::sleep(sf::milliseconds(100));
    }
}
