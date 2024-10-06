#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <limits.h>

#include "Square.hpp"

using namespace std;

class Player{

    private:

    
    string name;                    //The name of the player 
    int money;                      //Represent the amount of money the player have
    bool outOfJailCard {false};     //Out of jail card initilize to false
    bool in_jail;                   // True if the player is in Jail
    bool is_bankrupt;               // True if the player is in bankrupt


    vector<StreetSquare*> ownedStreets;    //vector that hold a pointer to owned street squares
    vector<TrainSquare*>  ownedTrain;      //vector that hold a pointer to owned train squares


    bool operator!=(const Player& other) const;


    public:

    //---------------Player initilize----------------
    //Constructor
    Player(std::string name, int money) : name(name), money(money), in_jail(false), is_bankrupt(false){};

    //Return the player name
    string get_name();


    //-----------Player's money handling-----------------

    //Return the amount of money the player have
    int get_money() const;

    //Pay the given amount of money
    bool sub_money(int);

    //Add the given amount of money to the player amount of money
    bool add_money(int);

    //Checks if the player can afford to subtract the given amount of money without quite
    bool can_afford(int);

    /*Player pay the rent for landing on other player asset
    Gets a pointer to the player object, and the amount to  */
    bool pay_rent(shared_ptr<Player> , int);


    //-----------Player's assets handling-----------------
    //Return the number of train the player have
    size_t train_num();

    //Add train to the vector after buy
    void add_train(TrainSquare&);

    //Add the street after purche
    void add_street(StreetSquare&);

    bool owns_all_color(const string& , const vector<shared_ptr<StreetSquare>>) const;

    bool can_build_balance(const string& ,  vector<shared_ptr<StreetSquare>> );

    int houses_in_owned();

    int hotels_in_owned();


    //-----------Player's jail handling-----------------

    int turnsInJail {0};

    //Return true if player have jail card
    bool get_jail_card();

    //Set sttate of jail card in case of earn/ use
    void set_jail_card(bool);

    //Is player in jail ?
    bool is_in_jail();

    //For free& set the player in jail
    void jail_state(bool);


    //-----------Bankrupt handling-----------------
    bool is_Bankrupt();

    void move_assets(shared_ptr<Player>);

    void clear_properties();


    //-------------------SFML handling------------------------
    sf::Texture playerTexture;      //SFML variables
    sf::Sprite  playerSprite;

    //Build a player object at the start of the game
    void init_player_vis(std::string path_to_img, sf::RenderWindow& window);

    //Get the current position of the player
    const sf::Vector2f& get_position() const;

    //Set a new position for the player according to the dice roll
    void set_position(const sf::Vector2f& new_position);


};
