#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

class Node
{
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinTree
{
public:
    Node* root;

    BinTree() : root(nullptr) {}

    void insert(int value)
    {
        root = insertRec(root, value);
    }

    void draw(sf::RenderWindow& window, Node* node, float x, float y, float offset)
    {
        if (node)
        {
            sf::CircleShape shape(20.f);
            shape.setFillColor(sf::Color::Green);
            shape.setPosition(x, y);

            sf::Font font;
            if (!font.loadFromFile("/Library/Fonts/Arial Unicode.ttf"))
            {
                std::cerr << "Error al cargar la fuente." << std::endl;
                return;
            }

            sf::Text text(std::to_string(node->data), font, 15);
            text.setFillColor(sf::Color::Black);
            text.setPosition(x + 5, y + 5);

            window.draw(shape);
            window.draw(text);

            if (node->left)
            {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x + 20.f, y + 20.f)),
                    sf::Vertex(sf::Vector2f(x - offset + 20.f, y + 80.f))
                };
                window.draw(line, 2, sf::PrimitiveType::Lines);
                draw(window, node->left, x - offset, y + 80, offset / 2);
            }

            if (node->right) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x + 20.f, y + 20.f)),
                    sf::Vertex(sf::Vector2f(x + offset + 20.f, y + 80.f))
                };
                window.draw(line, 2, sf::PrimitiveType::Lines);
                draw(window, node->right, x + offset, y + 80, offset / 2);
            }
        }
    }

private:
    Node* insertRec(Node* node, int value)
    {
        if (!node) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insertRec(node->left, value);
        }
        else {
            node->right = insertRec(node->right, value);
        }
        return node;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Binary Tree Visualization");

    BinTree tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(8);
    tree.insert(1);
    tree.insert(3);
    tree.insert(9);
    tree.insert(15);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        tree.draw(window, tree.root, 400, 20, 200); 
        window.display();
    }

    return 0;
}
