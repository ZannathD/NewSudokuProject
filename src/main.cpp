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

class Box
{
public:
    // Constructor: set everything once
    sf::RectangleShape shape;
    Box(float xCoord, float yCoord, float width, float height, sf::Color color = sf::Color::White)
    {
        shape.setSize({width, height});
        shape.setPosition({xCoord, yCoord});
        color.a = 200;
        shape.setFillColor(color);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(2.f);
    }
};




//Checking Sudoku board solution
bool Solution(int playerBoard[9][9])
{
   for (int row = 0; row < 9; row++)
   {
       std::unordered_set<int> rowSet;
       for (int column = 0; column < 9; column++)
       {
           //Check if any numbers are duplicated in row
           if (playerBoard[row][column] != 0 && rowSet.find(playerBoard[row][column]) != rowSet.end())
           {
              return false;
           }
           //Check that all boxes are filled
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
            //Check if any numbers are duplicated in column
            if (playerBoard[row][column] != 0 && colSet.find(playerBoard[row][column]) != colSet.end())
                {
                return false;
                }
            colSet.insert(playerBoard[row][column]);
            }
        }
    //Check if any numbers are duplicated in 3x3 grids
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
                            return false;
                        }
                        boxSet.insert(currentVal);
                    }
                }
            }
        }
    }
    return true;
}

//Function to keep player input inside the game board
void boundaryFix(int *selectedRowPtr, int *selectedColumnPtr)
{
    if (*selectedRowPtr == 9 && *selectedColumnPtr == 8 || *selectedRowPtr == 8 && *selectedColumnPtr == 9)
    {
        *selectedRowPtr = 0;
        *selectedColumnPtr = 0;
    }
    else if (*selectedRowPtr == -1 && *selectedColumnPtr == 0 || *selectedRowPtr == 0 && *selectedColumnPtr == -1)
    {
        *selectedRowPtr = 8;
        *selectedColumnPtr = 8;
    }
    else if (*selectedColumnPtr == -1)
    {
        *selectedColumnPtr = 8;
        *selectedRowPtr -= 1;
    }
    else if (*selectedColumnPtr == 9)
    {
        *selectedColumnPtr = 0;
        *selectedRowPtr += 1;
    }
    else if (*selectedRowPtr == -1)
    {
        *selectedRowPtr = 8;
        *selectedColumnPtr -= 1;
    }
    else if (*selectedRowPtr == 9)
    {
        *selectedRowPtr = 0;
        *selectedColumnPtr += 1;
    }
}

//Function to allow player to change values on sudoku board
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

//Function to CHECK if mouse is over buttons
bool isMouseOver(sf::RectangleShape& button, sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
}

//Function to SHOW if mouse is hovering a button
void mouseHoverColor(sf::RectangleShape& button, sf::RenderWindow& window)
{
    if (isMouseOver(button, window))
    {
        button.setFillColor(sf::Color(128,128,128));
    }
    else
    {
        button.setFillColor(sf::Color::White);
    }
}


int main()
{
    //Initializing variables
    int column, row, minutes = 0, difficulty = -1;;
    bool keyDownProcessed = false, complete = false, playGame = false, openSettings = false;

    //Sudoku Board specifications
    float boxSize = 60.f;
    sf::Color boxColor(255, 255,255, 200);
    sf::Color outlineColor(0, 0, 0);

    //Initialzing boards as arrays
    int playerBoard[9][9], initialBoard[9][9];

    int easyBoard [9][9] =
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
    int mediumBoard [9][9] =
        {
        {9, 0, 6, 2, 4, 8, 3, 0, 1},
        {4, 0, 7, 6, 1, 0, 5, 8, 9},
        {8, 0, 3, 0, 0, 0, 0, 2, 0},
        {6, 0, 0, 0, 0, 0, 1, 0, 7},
        {0, 8, 0, 7, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 1, 0, 6, 5},
        {0, 6, 0, 0, 8, 7, 9, 0, 0},
        {2, 9, 0, 1, 3, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 5, 0}
        };
    int hardBoard [9][9] =
        {
        {3, 1, 0, 7, 5, 9, 2, 0, 6},
        {2, 5, 0, 0, 0, 0, 0, 9, 0},
        {8, 7, 0, 6, 0, 3, 4, 5, 1},
        {0, 0, 9, 6, 0, 0, 0, 3, 4},
        {0, 0, 5, 0, 0, 8, 0, 0, 0},
        {0, 3, 0, 0, 0, 0, 6, 0, 8},
        {0, 9, 1, 2, 0, 6, 0, 0, 0},
        {0, 6, 0, 0, 0, 0, 0, 4, 0},
        {0, 0, 3, 5, 8, 0, 1, 0, 0}
        };


    //Setting font for difficulty and gameplay
    sf::Font font1;
    //Try-Catch for error handling
    try {
        if (!font1.openFromFile("../../assets/arial.ttf"))
        {
            throw std::runtime_error("Error loading font: ../../assets/arial.ttf");
        }
    } catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        return -1; // Indicate an error occurred
    }

    //Loading font for main menu screen
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

    //Difficulty Selection Background
    sf::Texture difficultyBackground;
    difficultyBackground.loadFromFile("../../assets/difficultyBkgrnd.jpg");
    sf::Sprite sprDifficultyBackground(difficultyBackground);
    sprDifficultyBackground.setScale(sf::Vector2f(.37f,.3125f));

    //Gameplay Background
    sf::Texture gameBackground;
    gameBackground.loadFromFile("../../assets/background.jpg");
    sf::Sprite sprBackground(gameBackground);

    //Settings Background
    sf::Texture settingsBackground;
    settingsBackground.loadFromFile("../../assets/settingsBackground.jpg");
    sf::Sprite sprSettings(settingsBackground);


    //Game puzzle completion image
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
    const sf::Texture texture("../../assets/newMM.jpg");
    sf::Sprite sprite(texture);
    sprite.setScale({1.1995,1.f});


    //Creating title of game on main menu
    sf::Text titleText(font2, "Single Soudoku", 100);
    titleText.setPosition(sf::Vector2f(460,260));
    titleText.setFillColor(sf::Color::Black);

    // Creating Button 1
    sf::RectangleShape button1(sf::Vector2f(200,50));
    button1.setPosition(sf::Vector2f(840,515));
    button1.setFillColor(sf::Color::White);
    button1.setOutlineColor(sf::Color::Black);
    button1.setOutlineThickness(2);
    //Creating Text for Button 1
    sf::Text button1Text(font2, "PLAY!",20);
    button1Text.setFillColor(sf::Color::Black);
    button1Text.setPosition({890.f, 530.f });


    //Create Button 2
    sf::RectangleShape button2(sf::Vector2f(200,50));
    button2.setPosition(sf::Vector2f(840,585));
    button2.setFillColor(sf::Color::White);
    button2.setOutlineColor(sf::Color::Black);
    button2.setOutlineThickness(2);
    //Button 2 text
    sf::Text button2Text(font2, "Settings",20);
    button2Text.setFillColor(sf::Color::Black);
    button2Text.setPosition(sf::Vector2f(885, 600));



    //Create Button 3
    sf::RectangleShape button3(sf::Vector2f(200,50));
    button3.setPosition(sf::Vector2f(840,655));
    button3.setFillColor(sf::Color::White);
    button3.setOutlineColor(sf::Color::Black);
    button3.setOutlineThickness(2);
    //Text for Button 3
    sf::Text button3Text(font2, "Quit",20);
    button3Text.setFillColor(sf::Color::Black);
    button3Text.setPosition({910.f, 670.f });

    //Return Button on Settings Menu
    Box settingsReturn(300, 900, 100, 50, sf::Color::White);
    // Make return text
    sf::Text settingsReturnText(font1, "Return",25);
    settingsReturnText.setPosition(sf::Vector2f(311, 910));
    settingsReturnText.setFillColor(sf::Color::Black);
    //Make Mute Button
    Box muteButton(960, 540, 100, 50, sf::Color::White);
    // Make Mute Text
    sf::Text muteButtonText(font1, "Mute",25);
    muteButtonText.setPosition(sf::Vector2f(980, 550));
    muteButtonText.setFillColor(sf::Color::Black);


    //Load music to play
    sf::Music music;
    if (!music.openFromFile("../../assets/chill_Lofi.wav"))
    {
        return -1; //error
    }
    music.play();


    //Start in-game timer
    sf::Clock clock;

    //Open game!
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        //Main menu button change color when moused over
        mouseHoverColor(button1, window);
        mouseHoverColor(button2, window);
        mouseHoverColor(button3, window);



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
        boundaryFix(&selectedRow, &selectedColumn);

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

        if (playGame == false && openSettings == false)
        {
            //Draw main menu
            window.draw(sprite);
            window.draw(button1);
            window.draw(button1Text);
            window.draw(button2);
            window.draw(button2Text);
            window.draw(button3);
            window.draw(button3Text);
            window.draw(titleText);

            //Check if they press play
            if (isButtonPressed(sf::Mouse::Button::Left))
            {
                if (isMouseOver(button1, window))
                {
                    playGame = true;
                    keyDownProcessed = true;
                    sleep(sf::milliseconds(300));
                }
            }
            if (isButtonPressed(sf::Mouse::Button::Left)) // Check if they press settings
            {
                if (isMouseOver(button2, window))
                {
                    openSettings = true;
                }
            }

            //Check if they want to close
            if(isButtonPressed(sf::Mouse::Button::Left))
            {
                if (isMouseOver(button3, window))
                {
                    window.close();
                }
            }
        }
        if (openSettings == true) //If settings is set to true, draw the settings background
        {
            window.draw(sprSettings);
            window.draw(settingsReturn.shape);
            window.draw(settingsReturnText);
            window.draw(muteButton.shape);
            window.draw(muteButtonText);
            mouseHoverColor(muteButton.shape, window);
            mouseHoverColor(settingsReturn.shape, window);

            if (isButtonPressed(sf::Mouse::Button::Left))
            {
                if (isMouseOver(muteButton.shape, window))
                {
                    music.stop();
                }
            }

            if (isButtonPressed(sf::Mouse::Button::Left))
            {
                if (isMouseOver(settingsReturn.shape, window))
                {
                    openSettings = false;
                }
            }

        }
        //If they did press play, prompt for difficulty
        else if (playGame == true && difficulty == -1)
        {
            window.draw(sprDifficultyBackground);

            //Easy button
            Box easyButton(370, 540, 100, 50, sf::Color::White);
            mouseHoverColor(easyButton.shape, window);
            window.draw(easyButton.shape);
            sf::Text easyButtonText(font1, "Easy",30);
            easyButtonText.setFillColor(sf::Color::Black);
            easyButtonText.setPosition(sf::Vector2f(385, 545));
            window.draw(easyButtonText);

            //Medium Button
            Box mediumButton(910, 540, 100, 50, sf::Color::White);
            mouseHoverColor(mediumButton.shape, window);
            window.draw(mediumButton.shape);
            sf::Text mediumButtonText(font1, "Medium",25);
            mediumButtonText.setFillColor(sf::Color::Black);
            mediumButtonText.setPosition(sf::Vector2f(913, 548));
            window.draw(mediumButtonText);

            //Hard Button
            Box hardButton(1450, 540, 100, 50, sf::Color::White);
            mouseHoverColor(hardButton.shape, window);
            window.draw(hardButton.shape);
            sf::Text hardButtonText(font1, "Hard",30);
            hardButtonText.setFillColor(sf::Color::Black);
            hardButtonText.setPosition(sf::Vector2f(1465, 545));
            window.draw(hardButtonText);


            if (isButtonPressed(sf::Mouse::Button::Left))
            {
                if (isMouseOver(easyButton.shape, window) && keyDownProcessed == false)
                {
                    for (int counter = 0; counter < 9; counter++)
                    {
                        for (int iterator = 0; iterator < 9; iterator++)
                        {
                            playerBoard[counter][iterator] = easyBoard[counter][iterator];
                            initialBoard[counter][iterator] = easyBoard[counter][iterator];
                        }
                    }
                    keyDownProcessed = true;
                    difficulty = 1;
                }
            }
            if (isButtonPressed(sf::Mouse::Button::Left))
            {
                if (isMouseOver(mediumButton.shape, window))
                {
                    for (int counter = 0; counter < 9; counter++)
                    {
                        for (int iterator = 0; iterator < 9; iterator++)
                        {
                            playerBoard[counter][iterator] = mediumBoard[counter][iterator];
                            initialBoard[counter][iterator] = mediumBoard[counter][iterator];
                        }
                    }
                    keyDownProcessed = true;
                    difficulty = 2;
                }
            }
            if (isButtonPressed(sf::Mouse::Button::Left))
            {
                if (isMouseOver(hardButton.shape, window))
                {
                    for (int counter = 0; counter < 9; counter++)
                    {
                        for (int iterator = 0; iterator < 9; iterator++)
                        {
                            playerBoard[counter][iterator] = hardBoard[counter][iterator];
                            initialBoard[counter][iterator] = hardBoard[counter][iterator];
                        }
                    }
                    keyDownProcessed = true;
                    difficulty = 3;
                }
            }
        }
        //If they pressed play and selected which difficulty
        else if (playGame == true && difficulty != -1)
        {
            window.draw(sprBackground);

            //Mouse input for selecting boxes on sudoku grid
            if (isButtonPressed(sf::Mouse::Button::Left))
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                selectedRow = (mousePos.y - 270) / boxSize;
                selectedColumn = (mousePos.x - 690) / boxSize;
            }

            //Creating blank sudoku grid
            for (column = 0; column < 9; column++)
            {
                for (row = 0; row < 9; row++)
                {
                    sf::RectangleShape box(sf::Vector2f(boxSize, boxSize));
                    box.setPosition(sf::Vector2f(690 + column * boxSize, 270 + row * boxSize));
                    // Apply shading to every other 3x3 block
                    int blockColumn = column / 3;
                    int blockRow = row / 3;
                    if ((blockColumn + blockRow) % 2 == 0) {
                        box.setFillColor(sf::Color(210,210,210,200));
                    } else {
                        box.setFillColor(boxColor);
                    }
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
            if (isMouseOver(checkButton, window))
            {
                checkButton.setFillColor(sf::Color(128,128,128));
            }
            else
            {
                checkButton.setFillColor(sf::Color::Green);
            }
            window.draw(checkButton);
            window.draw(checkButtonText);


            //Button to return to main menu
            Box returnButton(690, 880, 100, 50, sf::Color::White);
            mouseHoverColor(returnButton.shape, window);
            window.draw(returnButton.shape);
            sf::Text menu(font1, "Return", 28);
            menu.setFillColor(sf::Color::Black);
            menu.setPosition(sf::Vector2f(700, 885));
            window.draw(menu);

            if (isButtonPressed(sf::Mouse::Button::Left) && isMouseOver(returnButton.shape, window))
            {
                playGame = false;
                difficulty = -1;
                window.clear();
            }

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