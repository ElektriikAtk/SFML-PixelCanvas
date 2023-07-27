#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280

int main()
{
    int vertical_px = 8;
    int horizontal_px = 5;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SMFL Test Program");
    sf::Vector2f pixelSize(WINDOW_HEIGHT/vertical_px, WINDOW_HEIGHT/vertical_px);
    sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    background.setFillColor(sf::Color::Blue);
    sf::RectangleShape button(sf::Vector2f(300, 50));
    button.setPosition(sf::Vector2f(800,WINDOW_HEIGHT/4-button.getGlobalBounds().height/2));

    sf::Font font;
    if (!font.loadFromFile("misc/manrope-medium.ttf"))
    {
        // error...
    }

    sf::Text text;

    text.setFont(font);

    text.setCharacterSize(30);

    text.setFillColor(sf::Color::Green);

    text.setPosition(1000, 600);

    std::vector<sf::RectangleShape> pixelVector;
    for (int i = 0; i < WINDOW_HEIGHT; i += pixelSize.y) {
        sf::RectangleShape pixel(pixelSize);
        if (i != 0) {
            pixel.setPosition(sf::Vector2f(0, i));
        }
        pixel.setFillColor(sf::Color::White);
        pixel.setOutlineThickness(1.f);
        pixel.setOutlineColor(sf::Color::Black);
        pixelVector.push_back(pixel);

        for (int j = 0; j < pixelSize.x * horizontal_px; j += pixelSize.x) {
            pixel.setFillColor(sf::Color::White);
            pixel.setOutlineThickness(1.f);
            pixel.setOutlineColor(sf::Color::Black);
            pixel.setPosition(sf::Vector2f(j, i));
            pixelVector.push_back(pixel);
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(background);
        window.draw(button);
        window.draw(text);

        for (int k = 0; k != sizeof(pixelVector) * 4; k++) {
            window.draw(pixelVector[k]);
        }

        sf::Vector2i localPosition = sf::Mouse::getPosition(window); //Mouse pos
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //std::cout << "LocalPos: " << localPosition.x << ", " << localPosition.y << "\n";
            //std::cout << "\n";
            //std::cout << "Left: " << pixelVector[0].getGlobalBounds().left << std::endl;
            //std::cout << "Top: " << pixelVector[0].getGlobalBounds().top << std::endl;
            //std::cout << "Width: " << pixelVector[0].getGlobalBounds().width << std::endl;
            //std::cout << "Height: " << pixelVector[0].getGlobalBounds().height << std::endl;

            for (int k = 0; k != sizeof(pixelVector) * 4; k++) {

                int left = pixelVector[k].getGlobalBounds().left;
                int right = pixelVector[k].getGlobalBounds().left + pixelVector[k].getGlobalBounds().width;
                int top = pixelVector[k].getGlobalBounds().top;
                int bottom = pixelVector[k].getGlobalBounds().top + pixelVector[0].getGlobalBounds().height;

                if (localPosition.x > left && localPosition.x < right && localPosition.y > top && localPosition.y < bottom) {
                    pixelVector[k].setFillColor(sf::Color::Magenta);
                    window.draw(pixelVector[k]);                }
            }
        } 
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            pixelVector[30].setFillColor(sf::Color::Yellow);
            pixelVector[30].setOutlineColor(sf::Color(0, 0, 0));
            window.draw(pixelVector[30]);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        window.display();
    }
    return 0;
}
