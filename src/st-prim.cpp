#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "NodeDjikstra.h"
#include "graphHelper.h"

int main()
{
    const int width = 800;
    const int height = 600;

    int n_nodes = 30;
    NodeDj* nodeList[n_nodes];
    fillGraph<NodeDj>(nodeList, n_nodes, width, height, 1, std::min(3, n_nodes));
    std::vector<NodeDj*> visitedNodes;

    NodeDj* start = nodeList[0];
    start->setVisited(true);
    visitedNodes.push_back(start);

    const int radius = 3;
    sf::CircleShape nodeMarkers[n_nodes];
    for (int i = 0; i < n_nodes; ++i)
    {
        sf::CircleShape marker;
        marker.setPosition(nodeList[i]->x() - radius, nodeList[i]->y() - radius);
        marker.setRadius(radius);
        marker.setFillColor(sf::Color::Black);
        if (nodeList[i] == start) 
            marker.setFillColor(sf::Color::Blue);
        nodeMarkers[i] = marker;
    }

    sf::ContextSettings settings;
    settings.antialiasingLevel = 5;
    sf::RenderWindow window(sf::VideoMode(width, height), "Djikstra", sf::Style::Default, settings);
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

        if (visitedNodes.size() < n_nodes)
        {
            NodeDj* chosenNode = NULL;
            NodeDj* closestNeighbor = NULL;
            for (NodeDj* node: visitedNodes)
            {
                for (NodeDj* neighbor: node->neighbors())
                {
                    if (neighbor->visited()) continue;
                    if (chosenNode == NULL || closestNeighbor == NULL || node->distance(neighbor) < chosenNode->distance(closestNeighbor))
                    {
                        chosenNode = node;
                        closestNeighbor = neighbor;
                    }
                }
            }
            closestNeighbor->setVisited(true);
            closestNeighbor->setPrev(chosenNode);
            visitedNodes.push_back(closestNeighbor);

            if (visitedNodes.size() == n_nodes - 1)
                std::cout << "Minimum spanning tree discovered" << std::endl;
        }

        for (int i = 0; i < n_nodes; ++i)
            window.draw(nodeMarkers[i]);

        window.display();
        sf::sleep(sf::milliseconds(100));
    }
}
