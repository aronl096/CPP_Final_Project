#include "GUI_Manager.hpp"




// Set window reference
void Drawable::set_window(sf::RenderWindow& window) {
    this->window = &window;     // Store the pointer to the window
}



void Drawable::create_house(shared_ptr<Player> owner, StreetSquare& street){

    // Define the house shape as a triangle with a size to fit in 13x13 space
    sf::CircleShape* triangle = new sf::CircleShape(6.5f, 3);  // Now a pointer to match the asset type

    triangle->setFillColor(sf::Color::Cyan);
    triangle->setOutlineColor(sf::Color::White);
    triangle->setOutlineThickness(1.f); // Thin outline for the house

    int numHouses = street.houses; // Assuming 'houses' is a member variable of StreetSquare
        

    // Calculate the position of the house based on the street's location
    sf::Vector2f streetPosition(street.square_area.left, street.square_area.top); // Use left and top to get position
    sf::Vector2f housePosition = streetPosition + sf::Vector2f(numHouses * 15, 0); // Offset houses horizontally
        
    triangle->setPosition(housePosition); // Set the calculated position

    owner->add_asset(triangle);   // Add the house (triangle) to the player's assets 

    window->draw(*triangle);
    window->display();

}




void Drawable::create_hotel(std::shared_ptr<Player> owner, StreetSquare& street) {

    // Define the hotel shape as a rectangle with a size of 10x20
    sf::RectangleShape* hotel = new sf::RectangleShape(sf::Vector2f(10.f, 20.f));

    hotel->setFillColor(sf::Color::Red);         // Set hotel color to distinguish it
    hotel->setOutlineColor(sf::Color::White);    // Add a white outline
    hotel->setOutlineThickness(1.f);             // Thin outline for the hotel

    int numHouses = street.houses; // Assuming 'houses' is a member variable of StreetSquare

    // Calculate the position of the hotel based on the street's location
    sf::Vector2f streetPosition(street.square_area.left, street.square_area.top); // Use left and top to get position
    sf::Vector2f hotelPosition = streetPosition + sf::Vector2f(numHouses * 15, -20); // Offset hotel vertically by -20 for correct placement

    hotel->setPosition(hotelPosition); // Set the calculated position

    owner->add_asset(hotel);   // Add the hotel (rectangle) to the player's assets

    window->draw(*hotel);  // Draw the hotel
    window->display();     // Display the updated window

}



std::string Drawable::get_path_by_idx(int index) {
        
    switch (index) {
        case 1:
            return path_to_player1;
        case 2:
            return path_to_player2;
        case 3:
            return path_to_player3;
        case 4:
            return path_to_player4;
        case 5:
            return path_to_player5;
        case 6:
            return path_to_player6;
        case 7:
            return path_to_player7;
        case 8:
            return path_to_player8;
        default:
            return "Invalid index"; // Handle invalid index
        }
    
}
