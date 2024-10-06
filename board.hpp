#ifndef BOARD_HPP
#define BOARD_HPP


#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory> 
#include "Square.hpp"
#include "StreetSquare.hpp"


using namespace std;

class Board {

    private:
    sf::Texture boardTexture;
    sf::Sprite  boardSprite;
    static Board* singletonBoard;                //Singleton instance
    vector<unique_ptr<Square>> squares;          //represent the squares on board
    vector<shared_ptr<StreetSquare>> allStreets;
    Board();                                     //private constructor for Singleton

    
    public:

    // Static method to get the singleton instance
    static Board* get_instance();

    //Method that draw the board on the accepted window
    void render(sf::RenderWindow& window);

    //Return the square by the given position on board
    Square& get_square_by_position(const sf::Vector2f& position) ;

    Square& get_square_by_index(int) ;


    vector<shared_ptr<StreetSquare>> get_allStreets();


};



#endif
