#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

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
    for (int i = 0; i < pixelSize.y * vertical_px; i += pixelSize.y) {
        for (int j = 0; j <pixelSize.x * horizontal_px; j += pixelSize.x) {
            sf::RectangleShape pixel(pixelSize);
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

        for (int i = 0; i < pixelVector.size(); i++) {
            window.draw(pixelVector[i]);
        }

        sf::Vector2i localPosition = sf::Mouse::getPosition(window); //Mouse pos
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

            std::ofstream outputFile;
            outputFile.open("OutputFile.txt");

            for (int i = 0; i < pixelVector.size(); i++) {
                if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                    int left = pixelVector[i].getGlobalBounds().left;
                    int right = pixelVector[i].getGlobalBounds().left + pixelVector[i].getGlobalBounds().width;
                    int top = pixelVector[i].getGlobalBounds().top;
                    int bottom = pixelVector[i].getGlobalBounds().top + pixelVector[0].getGlobalBounds().height;

                    if (localPosition.x > left && localPosition.x < right && localPosition.y > top && localPosition.y < bottom) {
                        pixelVector[i].setFillColor(sf::Color::Black);
                        pixelVector[i].setOutlineColor(sf::Color::White);
                        window.draw(pixelVector[i]);
                        std::cout << i << "\n";
                    }
                }

                if (localPosition.x > button.getGlobalBounds().left && localPosition.x < button.getGlobalBounds().left + button.getGlobalBounds().width && localPosition.y > button.getGlobalBounds().top && localPosition.y < button.getGlobalBounds().top + button.getGlobalBounds().height) {
                    std::vector<int> bitmapVector;
                    text.setString("Inside");
                    for (int i = 0; i < pixelVector.size(); i++) {
                        sf::Color pixelColor = pixelVector[i].getFillColor();
                        if (pixelColor == sf::Color::Black) {
                            bitmapVector.push_back(1);
                        }
                        else {
                            bitmapVector.push_back(0);
                        }
                    }
                    for (int i = 0; i < bitmapVector.size(); i++) {
                        outputFile << "Bitmap vector: " << bitmapVector[i];
                        //std::cout << bitmapVector[i];
                    }

                    int decVal = 0;
                    for (int i = 7; i >= 0; i--) {
                        for (int j = 0; j < 8; j++) {
                            if (bitmapVector[i] == 1) {
                                std::cout << "j: " << j << "\n";
                                decVal += std::pow(2, j);
                            }
                        }
                        std::cout << "decval: " << decVal << "\n";
                    }
                }
                else {
                    text.setString("Outside");
                }
                window.draw(text);
                outputFile.close();
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
