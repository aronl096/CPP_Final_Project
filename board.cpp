#include "Board.hpp"



Board* Board::singletonBoard = nullptr;     //Initialize the singleton to nullptr


Board::Board() {


    SquareFactory factory;
    // Add all 40 slots with their respective names and positions on the board image

    //The bottom line
    squares.push_back(factory.create_square("Start Square", 0, sf::FloatRect(860, 826, 126, 124), {}));
    squares.push_back(factory.create_square("Street Square", 1, sf::FloatRect(782, 826, 78, 125), { "MEDITER - RANEAN AVENUE", "Brown"}));
    squares.push_back(factory.create_square("Community Chest Square", 2, sf::FloatRect(704, 826, 78, 125), {}));
    squares.push_back(factory.create_square("Street Square", 3, sf::FloatRect(626, 826, 78, 125), {"BALTIC AVENUE", "Brown"}));
    squares.push_back(factory.create_square("Tax Square", 4, sf::FloatRect(550, 826, 78, 125), {}));
    squares.push_back(factory.create_square("Train Square", 5, sf::FloatRect(472, 826, 78, 125), {}));
    squares.push_back(factory.create_square("Street Square", 6, sf::FloatRect(392, 826, 78, 125), {"ORIENTAL AVENUE", "Cyan"}));
    squares.push_back(factory.create_square("Surprise Square", 7, sf::FloatRect(314, 826, 78, 125), {}));
    squares.push_back(factory.create_square("Street Square", 8, sf::FloatRect(237, 826, 78, 125), {"VERMONT AVENUE", "Cyan"}));
    squares.push_back(factory.create_square("Street Square", 9, sf::FloatRect(158, 826, 126, 125), {"CONNECTICUT ANENUE", "Cyan"}));

    squares.push_back(factory.create_square("Jail Square", 10, sf::FloatRect(34, 826, 125, 125), {}));

    
    //The left row
    squares.push_back(factory.create_square("Street Square", 11, sf::FloatRect(35, 749, 125, 76), {"ST. CHARLES PLACE", "Pink"}));
    squares.push_back(factory.create_square("Company Square", 12, sf::FloatRect(35, 670, 125, 76), {}));
    squares.push_back(factory.create_square("Street Square", 13, sf::FloatRect(35, 593, 125, 76), {"STATES AVANUE", "Pink"}));
    squares.push_back(factory.create_square("Street Square", 14, sf::FloatRect(35, 516, 125, 76), {"VIRGINIA AVANUE", "Pink"}));
    squares.push_back(factory.create_square("Train Square", 15, sf::FloatRect(35, 436, 125, 76), {}));
    squares.push_back(factory.create_square("Street Square", 16, sf::FloatRect(35, 359, 125, 76), {"ST. JAMES PLACE", "Orange"}));
    squares.push_back(factory.create_square("Community Chest Square", 17, sf::FloatRect(35, 282, 125, 76), {}));
    squares.push_back(factory.create_square("Street Square", 18, sf::FloatRect(35, 203, 125, 76), {"TENNESSEE AVENUE", "Orange"}));
    squares.push_back(factory.create_square("Street Square", 19, sf::FloatRect(35, 126, 125, 76), {"NEW YORK AVENUE", "Orange"}));

    squares.push_back(factory.create_square("Free Parking Square", 20, sf::FloatRect(34, 0, 124, 124), {}));
    

    //The top line
    squares.push_back(factory.create_square("Street Square", 21, sf::FloatRect(160, 0, 126, 124), {"KENTUCKY AVENUE", "Red"}));
    squares.push_back(factory.create_square("Surprise Square", 22, sf::FloatRect(238, 0, 126, 124), {}));
    squares.push_back(factory.create_square("Street Square", 23, sf::FloatRect(316, 0, 126, 124), {"INDIANA ANENUE", "Red"}));
    squares.push_back(factory.create_square("Street Square", 24, sf::FloatRect(394, 0, 126, 124), {"ILLINOIS AVENUE", "Red"}));
    squares.push_back(factory.create_square("Train Square", 25, sf::FloatRect(471, 0, 126, 124), {}));
    squares.push_back(factory.create_square("Street Square", 26, sf::FloatRect(550, 0, 126, 124), {"ATLANTIC AVENUE", "Yellow"}));
    squares.push_back(factory.create_square("Street Square", 27, sf::FloatRect(627, 0, 126, 124), { "VENTNOR AVENUE", "Yellow"}));
    squares.push_back(factory.create_square("Company Square", 28, sf::FloatRect(705, 0, 126, 124), {}));
    squares.push_back(factory.create_square("Street Square", 29, sf::FloatRect(783, 0, 126, 124), {"MARVIN GARDENS", "Yellow"}));

    squares.push_back(factory.create_square("Go To Jail Square", 30, sf::FloatRect(861, 826, 124, 124), {}));
    

    //The right row
    squares.push_back(factory.create_square("Street Square", 31, sf::FloatRect(861, 126, 125, 76), {"PACIFIC AVENUE", "Green"}));
    squares.push_back(factory.create_square("Street Square", 32, sf::FloatRect(861, 203, 125, 76), {"NORTH CAROLINA AVENUE", "Green"}));
    squares.push_back(factory.create_square("Community Chest Square", 33, sf::FloatRect(861, 280, 125, 76), {}));
    squares.push_back(factory.create_square("Street Square", 34, sf::FloatRect(861, 359 ,125, 76), {"PENNSYLVANIA AVENUE", "Green"}));
    squares.push_back(factory.create_square("Train Square", 35, sf::FloatRect(861, 437, 125, 76), {}));
    squares.push_back(factory.create_square("Surprise Square", 36, sf::FloatRect(861, 516, 125, 76), {}));
    squares.push_back(factory.create_square("Street Square", 37, sf::FloatRect(861, 593, 125, 76), {"PARK PLACE", "Blue"}));
    squares.push_back(factory.create_square("Tax Square", 38, sf::FloatRect(861, 670, 125, 76), {}));
    squares.push_back(factory.create_square("Street Square", 39, sf::FloatRect(861, 749, 125, 76), {"BOARDWALK", "Blue"}));
    


     // Filter and copy ownership of StreetSquares
        for (const auto& square : squares) {
            // Attempt to cast the base class pointer (Square) to derived class (StreetSquare)
            if (StreetSquare* street = dynamic_cast<StreetSquare*>(square.get())) {
                // If the cast is successful, create a new unique_ptr for the StreetSquare
                this->allStreets.push_back(std::make_unique<StreetSquare>(*street)); // Copy the StreetSquare
        }
    }
}




Board* Board::get_instance() {

    if (!singletonBoard) {
        singletonBoard = new Board();
    }
    return singletonBoard;
}




void Board::render(sf::RenderWindow& window) {

    if (!this->boardTexture.loadFromFile("/home/user/Downloads/Board(6).jpg")) {
        throw std::string("Board image failed to open.");
    }
    this->boardSprite.setTexture(this->boardTexture);

    window.draw(boardSprite);
}


    
    
Square& Board::get_square_by_position(const sf::Vector2f& player_position) {

    for(const auto& square : squares){  
        
        //Check if the player's position is inside the square's area
        if(square->square_area.contains(player_position)){
            
            //Return a referance to the square
            return *square; 
        }
    }
    
    //If we didn't find the square
    throw out_of_range("Player isn't on a valid square.");

}




Square& Board::get_square_by_index(int index) {
    return *squares[index];
}




vector<shared_ptr<StreetSquare>> Board::get_allStreets(){
    return this->allStreets;
}
