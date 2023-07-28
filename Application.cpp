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
    sf::Vector2f pixelSize(WINDOW_HEIGHT / vertical_px, WINDOW_HEIGHT / vertical_px);
    sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    background.setFillColor(sf::Color::Blue);
    sf::RectangleShape button(sf::Vector2f(300, 50));
    button.setPosition(sf::Vector2f(800, WINDOW_HEIGHT / 4 - button.getGlobalBounds().height / 2));

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
        for (int j = 0; j < pixelSize.x * horizontal_px; j += pixelSize.x) {
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
        //while (window.pollEvent(event))
        //{
        //    if (event.type == sf::Event::Closed) {
        //        window.close();
        //    }
        //}


        window.clear();

        window.draw(background);
        window.draw(button);
        window.draw(text);

        for (int i = 0; i < pixelVector.size(); i++) {
            window.draw(pixelVector[i]);
        }

        sf::Vector2i localPosition = sf::Mouse::getPosition(window); //Mouse pos

        std::ofstream outputFile;
        outputFile.open("OutputFile.txt");


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            for (int i = 0; i < pixelVector.size(); i++) {
                int left = pixelVector[i].getGlobalBounds().left;
                int right = pixelVector[i].getGlobalBounds().left + pixelVector[i].getGlobalBounds().width;
                int top = pixelVector[i].getGlobalBounds().top;
                int bottom = pixelVector[i].getGlobalBounds().top + pixelVector[0].getGlobalBounds().height;

                if (localPosition.x > left && localPosition.x < right && localPosition.y > top && localPosition.y < bottom) {
                    pixelVector[i].setFillColor(sf::Color::Black);
                    pixelVector[i].setOutlineColor(sf::Color::White);
                    window.draw(pixelVector[i]);
                    //std::cout << i << "\n"; DEBUG
                }
                else {
                    text.setString("Outside");
                }
                window.draw(text);
            }
        }
                //outputFile.close();

        
        //---
                while (window.pollEvent(event))
                {
                    // check the type of the event...
                    switch (event.type)
                    {
                        // window closed
                    case sf::Event::Closed:
                        window.close();
                        break;

                        // key pressed
                    case sf::Event::MouseButtonReleased:
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            std::cout << "the left button was released" << std::endl;
                            if (event.mouseButton.x > button.getGlobalBounds().left && event.mouseButton.x < button.getGlobalBounds().left + button.getGlobalBounds().width && event.mouseButton.y > button.getGlobalBounds().top && event.mouseButton.y < button.getGlobalBounds().top + button.getGlobalBounds().height) {
                                std::vector<int> bitmapVector;
                                std::cout << "released in button boundaries\nPixelVector: " << pixelVector.size() << "\n";
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
                                std::cout << "BitmapVector BEFORE erase: ";
                                for (int i = 0; i < bitmapVector.size(); i++) {
                                    //outputFile << "Bitmap vector: " << bitmapVector[i]; DEBUG
                                    std::cout << bitmapVector[i];
                                }
                                std::cout << "\n";

                                //PROBLEM: Gets nibble per nibble and converts each one to a hex digit instead of getting two nibbles 
                                //and converting to full hex number (e.g. outputs 0x0A and 0x0F instead of 0xAF)

                                int hexSize = 3;
                                for (int j = bitmapVector.size(); j > 0; j -= hexSize + 1) {
                                    int decVal = 0;
                                    for (int i = hexSize; i >= 0; i--)
                                    {
                                        if (bitmapVector[i] == 1) {
                                            decVal += std::pow(2, (hexSize - i));
                                            std::cout << "i: " << (hexSize - i) << "\n";
                                            std::cout << "decVal: " << decVal << "\n";
                                        }
                                        //outputFile << "\ndecVal: " << decVal; Not working!
                                    }

                                    bitmapVector.erase(bitmapVector.begin(), bitmapVector.begin() + (hexSize+1));

                                    std::cout << "BitmapVector AFTER erase: ";
                                    for (int i = 0; i < bitmapVector.size(); i++) {
                                        //outputFile << "Bitmap vector: " << bitmapVector[i]; DEBUG
                                        std::cout << bitmapVector[i];
                                    }
                                    std::cout << "\n" << "bitmapVector size: " << bitmapVector.size() << "\n";

                                    std::string hexDigit;
                                    if (decVal > 9) {
                                        switch (decVal) {
                                        case 10:
                                            hexDigit = "A";
                                        case 11:
                                            hexDigit = "B";
                                        case 12:
                                            hexDigit = "C";
                                        case 13:
                                            hexDigit = "D";
                                        case 14:
                                            hexDigit = "E";
                                        case 15:
                                            hexDigit = "F";
                                        //default:
                                        //    hexDigit = "N/A";
                                        }
                                    }
                                    else {
                                        hexDigit = std::to_string(decVal);
                                    }
                                    std::cout << "hexDigit:" << "0x0" << hexDigit << "\n";
                                    std::cout << "j is: " << j << "\n\n\n";
                                }
                            }
                        }
                        break;

                        // we don't process other types of events
                    }
                }
        //---


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        window.display();
    }

    return 0;
}
