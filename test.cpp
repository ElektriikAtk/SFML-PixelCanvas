#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            shape.setFillColor(sf::Color::Red);
        }
        else {
            shape.setFillColor(sf::Color::Green);
        }

        window.draw(shape);
        window.display();
    }

    return 0;
}