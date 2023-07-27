#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280
#define SHAPE_SIZE 100.f

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
    sf::CircleShape shape(SHAPE_SIZE);
    shape.setFillColor(sf::Color::Green);
    shape.set

    sf::Font font;
    if (!font.loadFromFile("misc/manrope-medium.ttf"))
    {
        // error...
    }

    sf::Text text;

    text.setFont(font);

    text.setCharacterSize(24);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);

        sf::Vector2f shapePos = shape.getPosition();

        if (shapePos.x > 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                shape.move(-1.f, 0.f);
            }
        }

        if (shapePos.x < WINDOW_WIDTH - SHAPE_SIZE * 2 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                shape.move(1.f, 0.f);
            }
        }

        if (shapePos.y > 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                shape.move(0.f, -1.f);
            }
        }

        if (shapePos.y < WINDOW_HEIGHT - SHAPE_SIZE * 2 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            shape.move(0.f, 5.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                shape.move(0.f, 1.f);
            }
        }
        
        window.draw(text);

        window.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
    }

    return 0;
}