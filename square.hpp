#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <cmath>
#include <vector>
#include <random>

#include "player.hpp";


using namespace std;

class Square {
public:
    std::string square_type;    // Square type name 
    int index;                  // Index of the slot (0 to 39)
    sf::FloatRect square_area;  // Defines the area on the image for this slot

    Square(const std::string& name, int index, sf::FloatRect square_area)
        : square_type(name), index(index), square_area(square_area) {}

    virtual ~Square() = default;

    std::string get_type() { // Marked as const
        return square_type;
    }
};

//-----------------------------------------------------------------------------------------------------

class StreetSquare : public Square {
private:
    Player* owner;           // Pointer to the street owner
    int baseRentPrice {75};                  // The base rent price before house's building
    int rentWithHousePrice {85};             // Rent price with one house
    int rentWithHotelPrice {550};            // Rent price with hotel
    int streetPrice {250};                   // The street's price
    int housePrice {100};                    // House price
    int hotelPrice {500};                    //Hotel price
    bool hasHotel {false};                   // True if a hotel exists on the street
public:
    std::string streetName;                  // The name of the street (written on the board)
    std::string colorGroup;            // Color group of the street
    int houses {0};                          // Number of houses

    // Constructor
    StreetSquare(const std::string& name, int index, sf::FloatRect square_area,
                  std::string street ,std::string color)
        : Square(name, index, square_area), owner(nullptr) ,streetName(street), colorGroup(color) {};

    // Method that checks if the street has an owner
    Player* get_owner();

    // Set new owner
    void set_owner(Player*);

    // Return the price of the street
    int get_price();

    int get_house_price();

    int get_hotel_price();

    void set_hotel();

    // Calculate and return the rent price as a result of building houses/ hotels
    int calc_rent();

    // Method that checks whether a house can be built
    bool can_build_house(Player*);

    // Method that checks whether a hotel can be built
    bool can_build_hotel(Player*);

    // Promote the amount of the houses in the street after building
    void promote_houses();

    int houses_num();

    int hotel_num();
};

//----------------------------------------------------------------------------------------------------------


class SurpriseSquare : public Square {
private:
    // Calculate random index 
    int get_random_index();
public:
    SurpriseSquare(const std::string& name, int index, sf::FloatRect square_area) : Square(name, index, square_area) {};

    // Returns a random index to dynamically select a surprise card
    size_t get_card_index();
};

//----------------------------------------------------------------------------------------------------------


class TrainSquare : public Square {
private:
    Player* owner;
    int price {200}; // The train price
public:
    TrainSquare(const std::string& name, int index, sf::FloatRect square_area) 
        : Square(name, index, square_area), owner(nullptr) {};

    Player* get_owner() const {
        return this->owner;
    }

    void set_owner(Player* newOwner) {
        this->owner = newOwner;
    }

    // Calculate the rent price based on the number of trains the owner has
    int calc_rent() const {
        if(owner != nullptr ){
            return (owner->train_num()) * 50;
        }
        return 0;
    }

    // Return the train price
    int get_price() const {
        return this->price;
    }
};
// Class definitions for CompanySquare, StartSquare, GoToJailSquare, JailSquare, TaxSquare, FreeParkingSquare,
// and CommunityChestSquare remain unchanged and should be defined after TrainSquare.

class CompanySquare : public Square { // For water & electric company square
private:
    Player* owner;
    int companyPrice {150}; // The company price

public:
    CompanySquare(const std::string& name, int index, sf::FloatRect square_area) 
        : Square(name, index, square_area), owner(nullptr) {}

    void set_owner(Player* player) {
        this->owner = player;
    }

    Player* get_owner() const {
        return this->owner;
    }

    int get_price() const {
        return this->companyPrice;
    }
};

class StartSquare : public Square {
public:
    StartSquare(const std::string& name, int index, sf::FloatRect square_area) 
        : Square(name, index, square_area) {}
};

class GoToJailSquare : public Square {
public:
    GoToJailSquare(const std::string& name, int index, sf::FloatRect square_area) 
        : Square(name, index, square_area) {}
};

class JailSquare : public Square {
public:
    JailSquare(const std::string& name, int index, sf::FloatRect square_area) 
        : Square(name, index, square_area) {}
};

class TaxSquare : public Square {
private:
    int taxPrice {100};

public:
    TaxSquare(const std::string& name, int index, sf::FloatRect square_area) 
        : Square(name, index, square_area) {}

    int get_tax() const {
        return this->taxPrice;
    }
};

class FreeParkingSquare : public Square {
public:
    FreeParkingSquare(const std::string& name, int index, sf::FloatRect square_area) 
        : Square(name, index, square_area) {}
};

class CommunityChestSquare : public Square {
public:
    CommunityChestSquare(const std::string& name, int index, sf::FloatRect square_area) 
        : Square(name, index, square_area) {}
};

#endif
