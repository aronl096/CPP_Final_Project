using namespace std;

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <algorithm>

#include "Board.hpp"
#include "Square.hpp"
#include "Player.hpp"
#include "SpecialSquare.hpp"
#include "GUI_Manager.hpp"



class GameManager{

    private:
    Board* board;
    
    int numOfPlayers;
    int currPlayerIdx;
    bool double_outcome {false};
    int double_counter {0};
    Drawable obj;      //Store the image path


    //------------------------landing handling----------------------------------
    

    sf::Vector2f calc_player_position(std::shared_ptr<Player> player, Square& square);

    void handle_street_landing(shared_ptr<Player>, StreetSquare&);

    void handle_train_landing(shared_ptr<Player> , TrainSquare& );

    void handle_company_square(shared_ptr<Player>, CompanySquare&, int);


    //Handle the player's landing based on the respective square's functionality 
    void handle_player_landing(shared_ptr<Player> , Square& , int);



    //------------------------Player managment----------------------------------

    //Move the player to a specific square by her index
    void move_player_idx(shared_ptr<Player>  , size_t);

    /* A function that move the player on the board by the dice roll result 
       gets the new position and recognize the kind of the square */
    void move_player(shared_ptr<Player> , int );

    //Handle the surprise square 
    void handle_surprise_square(shared_ptr<Player> ,SurpriseSquare&);

    //Handle the surprise card by the given index
    void handle_surprise_card(shared_ptr<Player> , size_t);

    //Player buy a street
    void buy_street(shared_ptr<Player>, StreetSquare&);

    //Player buy a street
    void buy_train(shared_ptr<Player> , TrainSquare&);
    
    //Player buy a company
    void buy_company(shared_ptr<Player> , CompanySquare&); 

    //Player buy an house
    void build_house(shared_ptr<Player> , StreetSquare&,vector<shared_ptr<StreetSquare>>);

    //Playeer buy an hotel
    void build_hotel(shared_ptr<Player> , StreetSquare&,vector<shared_ptr<StreetSquare>>);

    //roll the dice
    int roll_dice();


    //Enter the player in jail / get him out 
    void set_jail_state(shared_ptr<Player>, bool);


    //------------------------Bankrupt handling--------------------------------

    //Handle nankruptcy as a result of getting to 0 NIS
    void handle_nankruptcy(shared_ptr<Player>);

    //Handle nankruptcy as a result of lack of ability to pay for other player 
    void handle_nankruptcy_(shared_ptr<Player>, shared_ptr<Player>);
    

    //--------------------------Game flow managment--------------------------------

    public:
    //Constructor
    GameManager() : board(nullptr), numOfPlayers(0), currPlayerIdx(0) {};
    vector<shared_ptr<Player>> players;



    //-----------Turn Handling----------------
    //Play the turn of the current player
    void play_turn();

    //Returns true if the game is over
    bool is_over();

    //Announce the winner of the game
    void announce_winner(shared_ptr<Player>);


    //----------------Initilize game-------------------------

    //Get the start position for locate the players on the start square
    sf::Vector2f get_start_position(int index);

    //Create the players objects
    void initialize_players(int , sf::RenderWindow& );

    //Initilize and draw the players on the board, the board – on the given window
    void initialize_game(sf::RenderWindow& window );

    // Start the game
    void start_game(sf::RenderWindow&);



};
