//Developers:         Dustin Lockhart, Simon Mekhail
//Class:              COP 2006 - CRN 14488
//Date:               March 25, 2025
//Description:        A program in C++ that allows a user to play a simple game of Sudoku
//Log:


#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>



int main()
{
    int column, row;
    int playerBoard [9][9] =
        {
        {2, 0, 0, 0, 6, 0, 0, 0, 0},
        {3, 0, 0, 0, 0, 2, 0, 8, 5},
        {6, 0, 0, 0, 0, 3, 1, 0, 0},
        {0, 2, 5, 9, 0, 0, 0, 7, 3},
        {9, 0, 7, 5, 8, 4, 2, 0, 6},
        {1, 4, 0, 0, 0, 7, 9, 5, 0},
        {0, 0, 9, 2, 0, 0, 0, 0, 1},
        {7, 8, 0, 4, 0, 0, 0, 0, 9},
        {0, 0, 0, 0, 9, 0, 0, 0, 4}
        };

    int initialBoard [9][9] =
    {
        {2, 0, 0, 0, 6, 0, 0, 0, 0},
        {3, 0, 0, 0, 0, 2, 0, 8, 5},
        {6, 0, 0, 0, 0, 3, 1, 0, 0},
        {0, 2, 5, 9, 0, 0, 0, 7, 3},
        {9, 0, 7, 5, 8, 4, 2, 0, 6},
        {1, 4, 0, 0, 0, 7, 9, 5, 0},
        {0, 0, 9, 2, 0, 0, 0, 0, 1},
        {7, 8, 0, 4, 0, 0, 0, 0, 9},
        {0, 0, 0, 0, 9, 0, 0, 0, 4}
    };

    //Sudoku Board specifications
    float boxSize = 60.f;
    sf::Color boxColor(255, 255,255);
    sf::Color outlineColor(0, 0, 0);

    //Setting up which font to use
    sf::Font font;
    if (!font.openFromFile("../assets/arial.ttf"))
    {
        std::cerr << "Error loading font!\n";
        return -1;
    }

    // Declaring text, and what text to use  -- RENAME -- NUMBERS ON BOARD --
    sf::Text text(font); //Declare the text object
    text.setFont(font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Regular);


    //User Input
    int selectedRow = -1, selectedColumn = -1;

    //Display beginning

    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);


    // Load Rabbids Picture
    sf::Texture texture;
    if (!texture.loadFromFile("../assets/IMG_2635.jpeg"))
    {
        return 0;
    }



    //Load music to play
    sf::Music music;
    if (!music.openFromFile("../assets/chill_Lofi.wav"))
    {
        return -1; //error
    }
    music.play();


    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            //Mouse input for selecting boxes
            if (isButtonPressed(sf::Mouse::Button::Left))
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                selectedRow = mousePos.y / boxSize;
                selectedColumn = mousePos.x / boxSize;
                if (selectedColumn >= 0 && selectedColumn < 9 && selectedRow >= 0 && selectedRow <9)
                {
                    //Checking what box was clicked
                    std::cout << "Selected cell: (" << selectedRow << ", " << selectedColumn << ")" << std::endl;
                }
                else
                {
                    //Default selected box/row so hitting numbers before clicking doesn't change anything
                    selectedColumn =  -1;
                    selectedRow = -1;
                }
            }
        }


        if (isKeyPressed(sf::Keyboard::Key::Down))
        {
            selectedRow = selectedRow + 1;
            //keyDownProcessed
            std::cout << selectedRow << std::endl;
            std::cout << selectedColumn << std::endl;
        }
        else if (isKeyPressed(sf::Keyboard::Key::Up))
        {
            selectedRow = selectedRow - 1;
            std::cout << selectedRow << std::endl;
            std::cout << selectedColumn << std::endl;
        }
        else if (isKeyPressed(sf::Keyboard::Key::Right))
        {
            selectedColumn = selectedColumn + 1;
            std::cout << "Row: " << selectedRow << std::endl;
            std::cout << "Column: " << selectedColumn << std::endl;
        }
        else if (isKeyPressed(sf::Keyboard::Key::Left))
        {
            selectedColumn = selectedColumn - 1;
            std::cout << selectedRow << std::endl;
            std::cout << selectedColumn << std::endl;
        }
        //Keyboard input for user to edit board
        if (selectedRow != -1 && selectedColumn != -1)
        {
            if (isKeyPressed(sf::Keyboard::Key::Num1))
            {
                playerBoard[selectedRow][selectedColumn] = 1;
            }
            else if (isKeyPressed(sf::Keyboard::Key::Num2))
            {
                playerBoard[selectedRow][selectedColumn] = 2;
            }
            else if (isKeyPressed(sf::Keyboard::Key::Num3))
            {
                playerBoard[selectedRow][selectedColumn] = 3;
            }
            else if (isKeyPressed(sf::Keyboard::Key::Num4))
            {
                playerBoard[selectedRow][selectedColumn] = 4;
            }
            else if (isKeyPressed(sf::Keyboard::Key::Num5))
            {
                playerBoard[selectedRow][selectedColumn] = 5;
            }
            else if (isKeyPressed(sf::Keyboard::Key::Num6))
            {
                playerBoard[selectedRow][selectedColumn] = 6;
            }
            else if (isKeyPressed(sf::Keyboard::Key::Num7))
            {
                playerBoard[selectedRow][selectedColumn] = 7;
            }
            else if (isKeyPressed(sf::Keyboard::Key::Num8))
            {
                playerBoard[selectedRow][selectedColumn] = 8;
            }
            else if (isKeyPressed(sf::Keyboard::Key::Num9))
            {
                playerBoard[selectedRow][selectedColumn] = 9;
            }
            else if (isKeyPressed(sf::Keyboard::Key::Num0))
            {
                playerBoard[selectedRow][selectedColumn] = 0;
            }
        }



        window.clear();



        //main menu code
        //Creating blank sudoku grid
        for (column = 0; column < 9; column++)
        {
            for (row = 0; row < 9; row++)
            {
                sf::RectangleShape box(sf::Vector2f(boxSize, boxSize));
                box.setPosition(sf::Vector2f(row * boxSize, column * boxSize));
                box.setFillColor(boxColor);
                box.setOutlineThickness(2.f);
                box.setOutlineColor(outlineColor);
                window.draw(box);

                }
            }


        //Filling out table with initial table and user table
        for (column = 0; column < 9; column++)
        {
            for (row = 0; row < 9; row++)
            {
                if (playerBoard[row][column] != 0 && initialBoard[row][column] == 0)
                {
                    sf::Text text(font, std::to_string(playerBoard[row][column]), 30);
                    text.setPosition(sf::Vector2f(column * boxSize + 20, row * boxSize + 15));
                    text.setFillColor(sf::Color::Blue);
                    window.draw(text);
                }
                if (initialBoard[row][column] != 0)
                {
                   // std::cout << "Text position: (" << column * boxSize + 20 << ", " << row * boxSize + 15 << ")" << std::endl;
                    sf::Text text(font, std::to_string(initialBoard[row][column]), 30);
                    text.setPosition(sf::Vector2f(column * boxSize + 20, row * boxSize + 15));
                    text.setFillColor(sf::Color::Black);
                    window.draw(text);
                }
            }


        }
        window.display();
    }
}

