//Developers:         Dustin Lockhart, Simon Mekhail
//Class:              COP 2006 - CRN 14488
//Date:               March 25, 2025
//Description:        A program in C++ that allows a user to play a simple game of Sudoku
//Log:                4/1 - added background and centered sudoku board on screen and made semi-transparent



#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>
#include <unordered_set>
#include <string>

//Make a header file

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
           if (playerBoard[row][column] == 0)
           {
               return false;
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


void boundaryFix(int &selectedRow, int &selectedColumn)
{
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
}

void playerValueInput (int playerBoard[9][9], int selectedRow, int selectedColumn)
{
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
}

bool isMouseOver(sf::RectangleShape& button, sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
}


int main()
{
    int column, row, minutes = 0;
    bool keyDownProcessed = false, complete = false;
    bool game = false;
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

    //useless basically
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
    sf::Color boxColor(255, 255,255, 200);
    sf::Color outlineColor(0, 0, 0);


    //Setting up which font to use
    sf::Font font1;
    if (!font1.openFromFile("../../assets/arial.ttf"))
    {
        std::cerr << "Error loading font!\n";
        return -1;
    }

    sf::Font font2;
    if (!font2.openFromFile("../../assets/JAPF.TTF"))
    {
        std::cerr << "Error loading font!\n";
        return -2;
    }

    //Check button
    sf::Text checkButtonText(font1, "Check", 30);
    checkButtonText.setStyle(sf::Text::Bold);
    checkButtonText.setPosition(sf::Vector2f(1137,885));
    checkButtonText.setFillColor(sf::Color::Black);

    //Gameplay Background
    sf::Texture background;
    background.loadFromFile("../../assets/background.jpg");
    sf::Sprite sprBackground(background);

    sf::Texture congrats;
    congrats.loadFromFile("../../assets/congrats.png");
    sf::Sprite sprCongrats(congrats);
    sprCongrats.setScale(sf::Vector2f(0.47f, 0.5f));
    sprCongrats.setPosition(sf::Vector2f(400, -150));

    //User Input default values for grid selection
    int selectedRow = -2, selectedColumn = -2;

    //Display beginning
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Sudoku, A C++ Project");
    window.setFramerateLimit(144);


    // Load Main Menu Image
    const sf::Texture texture("../../assets/IMG_MainMenu.jpg");
    sf::Sprite sprite(texture);
    sprite.setScale({0.5,1/2.f});


    //Creating title of game on main menu
    sf::Text titleText(font2, "Single Soudoku", 100);
    titleText.setPosition(sf::Vector2f(460,260));
    titleText.setFillColor(sf::Color::Black);

    // Creating Button 1
    sf::RectangleShape button1(sf::Vector2f(200,50));
    button1.setPosition(sf::Vector2f(840,515));
    button1.setFillColor(sf::Color::White);

    //Creating Text for Button 1
    sf::Text button1Text(font2, "PLAY!",20);
    button1Text.setFillColor(sf::Color::Black);
    //Text for Button 1 - position
    button1Text.setPosition({915.f, 530.f });


    //Create Button 2
    sf::RectangleShape button2(sf::Vector2f(200,50));
    button2.setPosition(sf::Vector2f(840,585));
    button2.setFillColor(sf::Color::White);
    //Text for Button 2
    sf::Text button2Text(font2, "Settings",20);
    button2Text.setFillColor(sf::Color::Black);
    //Text for Button 2 - position
    button2Text.setPosition({900.f, 600.f });


    //Create Button 3
    sf::RectangleShape button3(sf::Vector2f(200,50));
    button3.setPosition(sf::Vector2f(840,655));
    button3.setFillColor(sf::Color::White);
    //Text for Button 3
    sf::Text button3Text(font2, "Quit",20);
    button3Text.setFillColor(sf::Color::Black);
    //Text for Button 3 - position
    button3Text.setPosition({920.f, 670.f });


    //Load music to play
    sf::Music music;
    if (!music.openFromFile("../../assets/chill_Lofi.wav"))
    {
        return -1; //error
    }
    music.play();


    //Start in-game timer
    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        //Button 1 - Change color when hovering over
        if (isMouseOver(button1, window))
        {
            button1.setFillColor(sf::Color(128,128,128));
        }
        else
        {
            button1.setFillColor(sf::Color::White);
        }
        //Button 2 change color when hovering
        if (isMouseOver(button2, window))
        {
            button2.setFillColor(sf::Color(128,128,128));
        }
        else
        {
            button2.setFillColor(sf::Color::White);
        }
        //Button 3 change color when hovering
        if (isMouseOver(button3, window))
        {
            button3.setFillColor(sf::Color(128,128,128));
        }
        else
        {
            button3.setFillColor(sf::Color::White);
        }

        //Mouse input for selecting boxes
        if (isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            selectedRow = (mousePos.y - 270) / boxSize;
            selectedColumn = (mousePos.x - 690) / boxSize;
        }

        //Timer
        sf::Time timer = clock.getElapsedTime();
        int seconds = timer.asSeconds();
        if (seconds > 59)
        {
            seconds = 0;
            minutes += 1;
            clock.restart();
        }
        std::string full_Timer_String = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
        sf::Text textTimer(font1, full_Timer_String, 30);
        textTimer.setStyle(sf::Text::Bold);
        textTimer.setFillColor(sf::Color::Black);
        textTimer.setPosition(sf::Vector2f(937, 885));


        //Arrow keys to navigate board
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
        boundaryFix(selectedRow, selectedColumn);

        //Keyboard input for user to edit board
        playerValueInput (playerBoard, selectedRow, selectedColumn);


        //Reset stop for triggering event multiple times
        if (!isKeyPressed(sf::Keyboard::Key::Down) &&
                   !isKeyPressed(sf::Keyboard::Key::Up) &&
                   !isKeyPressed(sf::Keyboard::Key::Left) &&
                   !isKeyPressed(sf::Keyboard::Key::Right))
        {
            keyDownProcessed = false;  // Reset when no arrow key is pressed
        }



        window.clear();
        if (game == false)
        {
            window.draw(sprite);
            window.draw(button1);
            window.draw(button1Text);
            window.draw(button2);
            window.draw(button2Text);
            window.draw(button3);
            window.draw(button3Text);
            window.draw(titleText);
            if (isButtonPressed(sf::Mouse::Button::Left))
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (isMouseOver(button1, window))
                {
                    game = true;
                }
            }
            if(isButtonPressed(sf::Mouse::Button::Left))
            {

                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (isMouseOver(button3, window))
                {
                    window.close();
                }
            }
        }
        else
        {
            window.draw(sprBackground);

            //Creating blank sudoku grid
            for (column = 0; column < 9; column++)
            {
                for (row = 0; row < 9; row++)
                {
                    sf::RectangleShape box(sf::Vector2f(boxSize, boxSize));
                    box.setPosition(sf::Vector2f(690 + column * boxSize, 270 + row * boxSize));
                    box.setFillColor(boxColor);
                    //Highlighting selected cell for clarity
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
                        sf::Text playerNum(font1, std::to_string(playerBoard[row][column]), 30);
                        playerNum.setPosition(sf::Vector2f(690 + column * boxSize + 20, 270 + row * boxSize + 15));
                        playerNum.setFillColor(sf::Color::Blue);
                        window.draw(playerNum);
                    }
                    if (initialBoard[row][column] != 0)
                    {
                        sf::Text initialNum(font1, std::to_string(initialBoard[row][column]), 30);
                        initialNum.setPosition(sf::Vector2f(690 + column * boxSize + 20, 270 + row * boxSize + 15));
                        initialNum.setFillColor(sf::Color::Black);
                        window.draw(initialNum);
                    }
                }
            }
            //Timer display
            sf::RectangleShape timerBox(sf::Vector2f(100, 50));
            timerBox.setPosition(sf::Vector2f(910, 880));
            timerBox.setFillColor(sf::Color::White);
            timerBox.setOutlineColor(sf::Color::Black);
            timerBox.setOutlineThickness(2.f);
            window.draw(timerBox);
            window.draw(textTimer);

            //Check button
            sf::RectangleShape checkButton(sf::Vector2f(100,50));
            checkButton.setPosition(sf::Vector2f(1130,880));
            checkButton.setFillColor(sf::Color::Green);
            checkButton.setOutlineColor(sf::Color::Black);
            checkButton.setOutlineThickness(2.f);
            window.draw(checkButton);
            window.draw(checkButtonText);


            if (isButtonPressed(sf::Mouse::Button::Left) && (isMouseOver(checkButton, window)) && Solution(playerBoard) == 1)
            {
                complete = true;
            }
            if (complete == true)
            {
                window.draw(sprCongrats);
            }

        }
        window.display();
    }
}