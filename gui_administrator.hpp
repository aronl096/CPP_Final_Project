#ifndef GUI_MANAGER_HPP // Check if MY_HEADER_HPP is not defined
#define GUI_MANAGER_HPP  // Define MY_HEADER_HPP


#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>

#include "Player.hpp"
#include "StreetSquare.hpp"

using namespace std;

class Drawable{

    private:

    //Path to the player's images
    string path_to_player1 = "/home/user/Downloads/player1.png";
    string path_to_player2 = "/home/user/Downloads/player2.png";
    string path_to_player3 = "/home/user/Downloads/player3.png";
    string path_to_player4 = "/home/user/Downloads/player4.png";
    string path_to_player5 = "/home/user/Downloads/player5.png";
    string path_to_player6 = "/home/user/Downloads/player6.png";
    string path_to_player7 = "/home/user/Downloads/Player7.png";
    string path_to_player8 = "/home/user/Downloads/player8.png";


    public:
    sf::RenderWindow* window;

    // Constructor
    Drawable() : window(nullptr) {};


    // Set window reference
    void set_window(sf::RenderWindow& window);

    //Create & draw an house object on board
    void create_house(shared_ptr<Player> owner, StreetSquare& street);

    //Create & draw an house object on board
    void create_hotel(std::shared_ptr<Player> owner, StreetSquare& street);

    //Return the path to the player image by player index
    std::string get_path_by_idx(int index);


};


#endif GUI_MANAGER_HPP 
