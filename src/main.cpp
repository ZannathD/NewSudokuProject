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
#include <unordered_set>


//Checking Sudoku board
bool Solution(int playerBoard[9][9])
{
   for (int row = 0; row < 9; row++)
   {
       std::unordered_set<int> rowSet;
       for (int column = 0; column < 9; column++)
       {
           if (playerBoard[row][column] != 0)
           {
               if (rowSet.find(playerBoard[row][column]) != rowSet.end())
               {
                   return false;
               }
           }
           rowSet.insert(playerBoard[row][column]);
       }
   }

    for (int column = 0; column < 9; column++)
        {
        std::unordered_set<int> colSet;
        for (int row = 0; row < 9; ++row)
            {
            if (playerBoard[row][column] != 0)
                {
                if (colSet.find(playerBoard[row][column]) != colSet.end())
                    {
                    return false;  // Duplicate found in the column
                    }
                colSet.insert(playerBoard[row][column]);
                }
            }
        }
    for (int boxRow = 0; boxRow < 9; boxRow += 3)
    {
        for (int boxCol = 0; boxCol < 9; boxCol += 3)
        {
            std::unordered_set<int> boxSet;
            for (int counter = 0; counter < 3; counter++)
            {
                for (int iterator = 0; iterator < 3; iterator++)
                {
                    int currentVal = playerBoard[boxRow + counter][boxCol + iterator];
                    if (currentVal != 0)
                    {
                        if (boxSet.find(currentVal) != boxSet.end())
                        {
                            return false;  // Duplicate found in the box
                        }
                        boxSet.insert(currentVal);
                    }
                }
            }
        }
    }
    return true;
}


int main()
{
    int column, row;
    bool keyDownProcessed = false;
    int playerBoard [9][9] =
        {
        {0, 3, 0, 6, 0, 0, 0, 8, 0},
        {7, 8, 0, 1, 4, 9, 0, 0, 5},
        {1, 2, 4, 0, 3, 5, 0, 0, 0},
        {0, 5, 0, 7, 0, 0, 0, 1, 0},
        {0, 0, 2, 3, 0, 0, 0, 0, 6},
        {0, 1, 3, 0, 0, 0, 0, 4, 8},
        {0, 4, 0, 5, 1, 6, 3, 0, 9},
        {0, 0, 5, 2, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 9, 3, 5, 7, 2}
        };


    int initialBoard [9][9] =
    {
        {0, 3, 0, 6, 0, 0, 0, 8, 0},
        {7, 8, 0, 1, 4, 9, 0, 0, 5},
        {1, 2, 4, 0, 3, 5, 0, 0, 0},
        {0, 5, 0, 7, 0, 0, 0, 1, 0},
        {0, 0, 2, 3, 0, 0, 0, 0, 6},
        {0, 1, 3, 0, 0, 0, 0, 4, 8},
        {0, 4, 0, 5, 1, 6, 3, 0, 9},
        {0, 0, 5, 2, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 9, 3, 5, 7, 2}
    };

    int solnBoard [9][9] =
    {
     {5, 3, 9, 6, 2, 7, 1, 8, 4},
     {7, 8, 6, 1, 4, 9, 3, 2, 5},
     {1, 2, 4, 8, 3, 5, 6, 9, 7},
     {9, 5, 8, 7, 6, 4, 2, 1, 3},
     {4, 7, 2, 3, 8, 1, 9, 5, 6},
     {6, 1, 3, 9, 5, 2, 7, 4, 8},
     {2, 4, 7, 5, 1, 6, 8, 3, 9},
     {3, 9, 5, 2, 7, 8, 4, 6, 1},
     {8, 6, 1, 4, 9, 3, 5, 7, 2}
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
    int selectedRow = -2, selectedColumn = -2;

    //Display beginning

    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);


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
                    selectedColumn =  -2;
                    selectedRow = -2;
                }
            }
        }



        if (!keyDownProcessed)
        {
            if (isKeyPressed(sf::Keyboard::Key::Down))
            {
                selectedRow = selectedRow + 1;

                keyDownProcessed = true;
            }
            else if (isKeyPressed(sf::Keyboard::Key::Up))
            {
                selectedRow = selectedRow - 1;
                keyDownProcessed = true;

            }
            else if (isKeyPressed(sf::Keyboard::Key::Right))
            {
                selectedColumn = selectedColumn + 1;
                keyDownProcessed = true;

            }
            else if (isKeyPressed(sf::Keyboard::Key::Left))
            {
                selectedColumn = selectedColumn - 1;
                keyDownProcessed = true;

            }
        }

        //Keeping selected Row / Column in the bounds of the board
        if (selectedRow == 9 && selectedColumn == 8 || selectedRow == 8 && selectedColumn == 9)
        {
            selectedRow = 0;
            selectedColumn = 0;
        }
        else if (selectedRow == -1 && selectedColumn == 0 || selectedRow == 0 && selectedColumn == -1)
        {
            selectedRow = 8;
            selectedColumn = 8;
        }
        else if (selectedColumn == -1)
        {
            selectedColumn = 8;
            selectedRow -= 1;
        }
        else if (selectedColumn == 9)
        {
            selectedColumn = 0;
            selectedRow += 1;
        }
        else if (selectedRow == -1)
        {
            selectedRow = 8;
            selectedColumn -= 1;
        }
        else if (selectedRow == 9)
        {
            selectedRow = 0;
            selectedColumn += 1;
        }



        //Reset stop for triggering event multiple times
        if (!isKeyPressed(sf::Keyboard::Key::Down) &&
                   !isKeyPressed(sf::Keyboard::Key::Up) &&
                   !isKeyPressed(sf::Keyboard::Key::Left) &&
                   !isKeyPressed(sf::Keyboard::Key::Right))
        {
            keyDownProcessed = false;  // Reset when no arrow key is pressed
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


        //Creating blank sudoku grid
        for (column = 0; column < 9; column++)
        {
            for (row = 0; row < 9; row++)
            {
                sf::RectangleShape box(sf::Vector2f(boxSize, boxSize));
                box.setPosition(sf::Vector2f(column * boxSize, row * boxSize));
                box.setFillColor(boxColor);
                if (column == selectedColumn && row == selectedRow)
                {
                    box.setFillColor(sf::Color::Yellow);
                }
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
    std::cout << Solution(playerBoard) << std::endl;
}

