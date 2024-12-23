/*

TODO:
- Fix all "???" marked comments
- Make proper markdown changelog
- Remove unnecessary global variables
- Optimize/minimize code
- Implement functionality to choose between touchpen and mouse
- ^ Fix double click to paint issue
- Fix output of hex values to file
- Fix app icon (https://github.com/SFML/SFML/wiki/Tutorial%3A-Create-and-Use-SetIcon)
- Fix warnings (data loss at converion)

*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PixelCanvas");
    int vertical_px = 8;
    int horizontal_px = 5;
    float pixelOutlineThickness = 2.f;
    int canvasPadding = 5;
    sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    sf::RectangleShape button(sf::Vector2f(300, 50));
    sf::Vector2f buttonCoords(800.f, WINDOW_HEIGHT / 4 - button.getGlobalBounds().height / 2);
    sf::Vector2f pixelSize(WINDOW_HEIGHT / vertical_px - canvasPadding, WINDOW_HEIGHT / vertical_px - canvasPadding);
    sf::Text text;
    sf::Text buttonText;
    std::string buttonString = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string color = "Black"; // Find better method! Maybe bool implementation? Bitmasking?
    sf::Font font;
    sf::Color pixelOutlineColor = sf::Color(96, 96, 96, 255);
    sf::Color canvasOutlineColor = sf::Color::Black;
    //int ButtonCharSize = 10;
    int charSize = 30;
    int buttonCharSize = 20;
    int pixelScaleFactor = 4;
    int canvasHeight = pixelSize.y * vertical_px + pixelOutlineThickness * 2;
    int canvasWidth = pixelSize.x * horizontal_px + pixelOutlineThickness*2;
    int buttonTextPadding = 50;
    background.setFillColor(sf::Color(0, 100, 180, 255));
    //buttonText.setCharacterSize(charSize);


    buttonText.setString(buttonString);
    buttonText.setFillColor(sf::Color::Magenta);
    buttonText.setPosition(buttonCoords.x, buttonCoords.y);
    button.setPosition(buttonCoords.x, buttonCoords.y);
    button.setOutlineThickness(2.f);
    button.setOutlineColor(sf::Color::Black);
    text.setCharacterSize(charSize);
    text.setFillColor(sf::Color::Green);
    text.setPosition(1000, 600);
    //std::cout <<buttonText.getLocalBounds().width<<"\n";

    if (!font.loadFromFile("misc/VT323-Regular.ttf")) {
        std::cout << "The chosen font could not be loaded.\n";
    } else {
        text.setFont(font);
        buttonText.setFont(font);
    }

    std::vector<sf::RectangleShape> pixelVector; // Each pixel in the canvas is stored here
    for (int i = canvasPadding*(pixelScaleFactor); i <  canvasHeight; i += pixelSize.y) { // Each row? of pixels
        for (int j = canvasPadding*(pixelScaleFactor); j < canvasWidth; j += pixelSize.x) { // Each column? of pixels
            sf::RectangleShape pixel(pixelSize); // Each pixel gets created (initialized) with given parameters
            pixel.setOutlineThickness(pixelOutlineThickness);
            pixel.setOutlineColor(pixelOutlineColor);
            pixel.setPosition(sf::Vector2f(j, i));
            pixelVector.push_back(pixel);
        }
    }

    sf::RectangleShape canvasOutline(sf::Vector2f(canvasWidth, canvasHeight)); // Border around the pixel canvas
    sf::Vector2f canvasOutlinePos(pixelVector[0].getPosition().x - pixelOutlineThickness, pixelVector[0].getPosition().y - pixelOutlineThickness);
    canvasOutline.setPosition(canvasOutlinePos);
    canvasOutline.setOutlineThickness(canvasPadding);
    canvasOutline.setOutlineColor(canvasOutlineColor);
    canvasOutline.setFillColor(sf::Color::Transparent);


    while (window.isOpen())
    {
        while (buttonText.getGlobalBounds().width + buttonTextPadding >  button.getGlobalBounds().width) { /// ???
            buttonText.setCharacterSize(buttonCharSize);
        }
        buttonText.setPosition(button.getPosition().x + (button.getGlobalBounds().width - buttonText.getGlobalBounds().width) / 2, button.getPosition().y);

        // ???
        sf::RectangleShape testRect(sf::Vector2f(buttonText.getGlobalBounds().width, 2*buttonText.getGlobalBounds().height));
        testRect.setPosition(buttonText.getPosition().x, buttonText.getPosition().y);
        testRect.setOutlineColor(sf::Color::Red);
        testRect.setOutlineThickness(1.f);
        testRect.setFillColor(sf::Color::Transparent);

        window.clear();
        window.draw(background);
        window.draw(canvasOutline);
        window.draw(button);
        window.draw(buttonText);
        window.draw(text);
        window.draw(testRect);

        for (int i = 0; i < pixelVector.size(); i++) {
            window.draw(pixelVector[i]); // Each pixel is "shown" since it was initialized before (in their respective positions)
        }

        sf::Vector2i localPosition = sf::Mouse::getPosition(window); // Mouse position inside each pixel in canvas

        std::ofstream outputFile;
        outputFile.open("OutputFile.txt");

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            for (int i = 0; i < pixelVector.size(); i++) {
                // Probably not the best way to do this...
                int left = pixelVector[i].getGlobalBounds().left;
                int right = pixelVector[i].getGlobalBounds().left + pixelVector[i].getGlobalBounds().width;
                int top = pixelVector[i].getGlobalBounds().top;
                int bottom = pixelVector[i].getGlobalBounds().top + pixelVector[0].getGlobalBounds().height;
                // Decides what happens depending on which pixel on the canvas the mouse clicks on
                if (localPosition.x > left && localPosition.x < right && localPosition.y > top && localPosition.y < bottom) {
                    // Each pixel in the canvas gets painted a different color depending on the current color
                    if (pixelVector[i].getFillColor() == sf::Color::White && color == "Black") {
                        pixelVector[i].setFillColor(sf::Color::Black);
                        pixelVector[i].setOutlineColor(pixelOutlineColor);
                        window.draw(pixelVector[i]);
                    }
                    else if (pixelVector[i].getFillColor() == sf::Color::Black && color == "White") {
                        pixelVector[i].setFillColor(sf::Color::White);
                        pixelVector[i].setOutlineColor(pixelOutlineColor);
                        window.draw(pixelVector[i]);
                    }
                }
                else {
                    //text.setString("Outside");
                }
                window.draw(text);
            }
        }
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            // check the type of the event...
            switch (event.type)
            {
                // window closed
            case sf::Event::Closed:
            {
                window.close();
            }
            break;

                // Mouse pressed
            case sf::Event::MouseButtonReleased:
            {
                if (color == "Black") {
                    color = "White";
                }
                else {
                    color = "Black";
                }

                bool leftMouseClicked = event.mouseButton.button == sf::Mouse::Left;
                bool mouseInsideButton = event.mouseButton.x > button.getGlobalBounds().left && event.mouseButton.x < button.getGlobalBounds().left + button.getGlobalBounds().width && event.mouseButton.y > button.getGlobalBounds().top && event.mouseButton.y < button.getGlobalBounds().top + button.getGlobalBounds().height;
                if (leftMouseClicked && mouseInsideButton) {
                    std::vector<int> bitmapVector;
                    //text.setString("Inside");
                    for (int i = 0; i < pixelVector.size(); i++) {
                        sf::Color pixelColor = pixelVector[i].getFillColor();
                        if (pixelColor == sf::Color::Black) { // ???
                            bitmapVector.push_back(1);
                        }
                        else {
                            bitmapVector.push_back(0);
                        }
                    }

                    // Idk what is going on in here ???
                    int hexSize = 3;
                    std::string hexDigit;
                    for (int j = bitmapVector.size(); j > 0 && bitmapVector.size() > 0; j -= hexSize + 1) {
                        // Something to do with the 1st and 2nd digits in hex as in 0x12 ???
                        std::string hexDigit0;
                        std::string hexDigit1;
                        for (int k = 0; k < 2; k++) {
                            if (bitmapVector.size() >= 0) {
                                int decVal = 0;
                                for (int i = hexSize; i >= 0; i--)
                                {
                                    if (bitmapVector[i] == 1) {
                                        decVal += (int)round(std::pow(2, (hexSize - i))); //Necessary to round?
                                    }
                                }

                                if (decVal > 9) {
                                    switch (decVal) {
                                    case 10:
                                        hexDigit = "A";
                                        break;
                                    case 11:
                                        hexDigit = "B";
                                        break;
                                    case 12:
                                        hexDigit = "C";
                                        break;
                                    case 13:
                                        hexDigit = "D";
                                        break;
                                    case 14:
                                        hexDigit = "E";
                                        break;
                                    case 15:
                                        hexDigit = "F";
                                        break;
                                        //default:
                                        //    hexDigit = "N/A";
                                        //    break;
                                    }
                                }
                                else {
                                    hexDigit = std::to_string(decVal); // Why ???
                                }

                                if (bitmapVector.size() > 0) { // CODE WILL CRASH WITHOUT THIS! Check why ???
                                    bitmapVector.erase(bitmapVector.begin(), bitmapVector.begin() + (hexSize + 1));
                                }


                                if (k == 0)
                                {
                                    hexDigit0 = hexDigit;
                                }
                                else if (k == 1)
                                {
                                    hexDigit = hexDigit0 + hexDigit;
                                    std::cout << "hexDigit: 0x" << hexDigit << "\n";
                                }
                            }
                        }
                    }
                    std::cout << std::endl; // Add en end line after very hex digit printout
                }
            }
            break;

            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left) {

                }
            }
            break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        window.display();
    }

    return 0;
}
