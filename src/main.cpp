//Developers:         Dustin Lockhart, Simon Mekhail
//Class:              COP 2006 - CRN 14488
//Date:               March 25, 2025
//Description:        A program in C++ that allows a user to play a simple game of Sudoku
//Log:


#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



int main()
{
    int column, row;
    int board [9][9] =
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
/*
    sf::Font font("arial.ttf");
    sf::Text text(font);
*/
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    // Load Rabbids Picture
    /*sf::Texture texture;
    if (!texture.loadFromFile("IMG_2635.jpeg")
    {
        return 0;
    }*/


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
        }

        window.clear();
/*
        for (column = 0; column < 9; column++)
        {
            for (row = 0; row < 9; row++)
            {
                text.setString(std::to_string(board[row][column]));
                text.setPosition(sf::Vector2f(column * 50 + 15, row * 50+10));
                window.draw(text);
            }
        }
*/
        window.display();
    }
}

