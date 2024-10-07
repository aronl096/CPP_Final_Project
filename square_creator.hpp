
#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Square.hpp"




class SquareFactory {
public:
    SquareFactory() {};

    // Create in runtime the requested square
    Square* create_square(const std::string& type, int index, sf::FloatRect square_area, std::vector<std::string> extra_args);
};

#endif 
