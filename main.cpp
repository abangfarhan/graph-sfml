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

    int n_nodes = 3;
    Node n1("A", 10, 10);
    Node n2("B", 100, 150);
    Node n3("C", 30, 450);
    n1.addNeighbor(&n2);
    n1.addNeighbor(&n2);
    n1.addNeighbor(&n3);
    n2.addNeighbor(&n3);
    Node* nodeList[n_nodes] = {&n1, &n2, &n3};

    sf::CircleShape nodeCircles[n_nodes];
    for (int i = 0; i < n_nodes; ++i)
    {
        nodeCircles[i].setRadius(10);
        nodeCircles[i].setPosition(sf::Vector2f(nodeList[i]->x() - 10, nodeList[i]->y() - 10));
        nodeCircles[i].setFillColor(sf::Color(0, 0, 0, 30));
    }
    // Node nodes[3] = {n1, n2, n3};
    // for (int i = 0; i < 3; ++i)
    // {
    //     std::cout << "Node " << nodes[i].name() << std::endl;
    //     std::cout << "  x = " << nodes[i].x() << std::endl;
    //     std::cout << "  y = " << nodes[i].y() << std::endl;
    //     std::cout << "  Neighbors " << std::endl;
    //     for (Node* node: nodes[i].neighbors())
    //     {
    //         std::cout << "    " << node->name() << std::endl;
    //     }
    // }

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
    // line pointing down-left and top-left must be incremented by 180 deg
    angle = atan((y2 - y1) / (x2 - x1)) * 180/PI;
    if (x2 - x1 < 0) angle += 180;

    line.setSize(sf::Vector2f(len, 1));
    line.setFillColor(sf::Color::Red);
    line.setRotation(angle);
    return line;
}
