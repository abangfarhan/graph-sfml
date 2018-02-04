#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "Node.h"

#define PI 3.14159265

sf::RectangleShape Line(float x1, float y1, float x2, float y2);

int main()
{
    const int width = 800;
    const int height = 600;

    int n_nodes = 4;
    Node* nodeList[n_nodes] = {
        new Node(10, 300, "A"),
        new Node(50, 100, "B"),
        new Node(50, 500, "C"),
        new Node(200, 400, "D")
    };
    nodeList[0]->addNeighbor(nodeList[1]);
    nodeList[0]->addNeighbor(nodeList[2]);
    nodeList[1]->addNeighbor(nodeList[2]);
    nodeList[1]->addNeighbor(nodeList[3]);
    nodeList[2]->addNeighbor(nodeList[3]);
    // nodeList[0]->addNeighbor(nodeList[1]);
    // nodeList[0]->addNeighbor(nodeList[2]);
    // nodeList[1]->addNeighbor(nodeList[2]);
    // nodeList[3]->addNeighbor(nodeList[0]);
    // nodeList[3]->addNeighbor(nodeList[2]);
    // print nodes info
    for (int i = 0; i < n_nodes; ++i)
    {
        std::cout << "Node " << nodeList[i] << std::endl;
        std::cout << "  Coordinate: (" << nodeList[i]->x() << ", " << nodeList[i]->y() << ")" << std::endl;
        std::cout << "  Neighbors: " << std::endl;
        for (Node* neighbor: nodeList[i]->neighbors())
            std::cout << "  - " << neighbor << " - Distance: " << nodeList[i]->distance(neighbor) << std::endl;
    }

    Node* nodeListSpanning[n_nodes];
    for (int i = 0; i < n_nodes; ++i)
        nodeListSpanning[i] = new Node(nodeList[i]);

    sf::CircleShape nodeCircles[n_nodes];
    for (int i = 0; i < n_nodes; ++i)
    {
        float radius = 10;
        nodeCircles[i].setRadius(radius);
        nodeCircles[i].setPosition(sf::Vector2f(nodeList[i]->x() - radius, nodeList[i]->y() - radius));
        nodeCircles[i].setFillColor(sf::Color(0, 0, 0, 30));
    }

    sf::RenderWindow window(sf::VideoMode(width, height), "Graph");
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
            window.draw(nodeCircles[i]);
            for (Node* neighbor: nodeList[i]->neighbors())
            {
                sf::RectangleShape line = Line(nodeList[i]->x(), nodeList[i]->y(), neighbor->x(), neighbor->y());
                window.draw(line);
            }

            for (Node* neighbor: nodeListSpanning[i]->neighbors())
            {
                sf::RectangleShape line = Line(nodeListSpanning[i]->x(), nodeListSpanning[i]->y(), neighbor->x(), neighbor->y());
                line.setFillColor(sf::Color::Blue);
                window.draw(line);
            }
        }

        window.display();
    }
}

sf::RectangleShape Line(float x1, float y1, float x2, float y2)
{
    sf::RectangleShape line;
    float len, angle;

    line.setPosition(x1, y1);
    len = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    angle = atan((y2 - y1) / (x2 - x1)) * 180/PI;
    // line pointing down-left and top-left must be incremented by 180 deg
    if (x2 - x1 < 0) angle += 180;

    line.setSize(sf::Vector2f(len, 1));
    line.setFillColor(sf::Color(100, 100, 100));
    line.setRotation(angle);
    return line;
}
