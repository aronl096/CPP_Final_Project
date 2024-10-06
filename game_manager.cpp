#include "GameManager.hpp"



sf::Vector2f GameManager::calc_player_position(std::shared_ptr<Player> player, Square& square) {

    // Get the total number of players on this square using square_area.contains()
    int playersOnSquare = 0;
    for (const auto& p : players) {
        // Dereference the shared_ptr to access the player's position
        sf::Vector2f playerPos(p->get_position()); // assuming Player has get_position_x and get_position_y methods
        if (square.square_area.contains(playerPos)) {
            playersOnSquare++;
        }
    }

    // The base position of the square (top-left corner)
    sf::Vector2f squarePosition(square.square_area.left, square.square_area.top);

    // Calculate offset based on the number of players on the same square to avoid overlapping
    float offsetX = 10.0f * (playersOnSquare % 2); // adjust horizontally for players
    float offsetY = 10.0f * (playersOnSquare / 2); // adjust vertically if more than 2 players

    // Final player position: the base square position plus some offset
    sf::Vector2f playerPosition = squarePosition + sf::Vector2f(offsetX, offsetY);

    return playerPosition;
}


void GameManager::move_player_idx(shared_ptr<Player> player, size_t index){

    //Gets the current position of the player & the square he is on
    Square& curr_square = board->get_square_by_position(player->get_position());

    //Calculate the new position by the dice roll result
    Square& new_square= board->get_square_by_index(index); // 40 squares is on the board

    int steps = index + curr_square.index;
    //Passing the starting square entitles you to NIS 200 
    //In porpuse to get the jail square, the player donsen't collect 200 NIS
    if(steps >= 40 && new_square.get_type() != "Go To Jail Square"){
        player->add_money(200);
    }

    //Calculate the player position on the new square
    sf::Vector2f new_position = calc_player_position(player, new_square);

    //Set the player on the new square
    player->set_position(new_position);

    handle_player_landing(player, new_square, steps%40);

}




void GameManager::move_player(shared_ptr<Player>  player, int rollDice){

    //Gets the current position of the player & the square he is on
    Square& curr_square = board->get_square_by_position(player->get_position());

    //Calculate the new position by the dice roll result
    Square& new_square= board->get_square_by_index((curr_square.index + rollDice)%40); // 40 squares is on the board


    //Passing the starting square entitles you to NIS 200
    if(curr_square.index + rollDice >= 40){ 
        player->add_money(200);
    }

    // Create an sf::Vector2f from the new square's top-left corner
    sf::Vector2f new_position(new_square.square_area.left +10.f, new_square.square_area.top +10.f);

    // Move the player to the new square's position
    player->set_position(new_position);

    //handle the square functionality
    handle_player_landing(player, new_square, rollDice);

    }





//---------------------------------------Handle player landing---------------------------------------------------------



void GameManager::handle_street_landing(shared_ptr<Player> player, StreetSquare& street){
    
    cout << player->get_name() <<" land in " << street.streetName <<endl;
    cout << "The amount of money you have is :" << player->get_money() <<endl;

        //In case the street has no owner
        if(!street.get_owner()){
            cout << "The street has no owner, would you like to buy it in: " << street.get_price() <<" NIS ? \n Enter: Y (for yes) or N (For no)" << endl;
            char ans;
            cin>>ans;//Get the input from the player

            if(ans == 'Y' ){
                //Player want to buy the street
                buy_street(player, street);
            }

            else{
                cout << "You decide to not buy ." <<endl;
            }
        }

        //If the owner of the street is player
        if(street.get_owner() = player){
            cout << "You are the owner of " << street.streetName << " ." << " Would you like to build an house or hotle ?" << endl;
            cout << "If you want to build an house enter A, If you want to build an hotel enter B, for none enter N ." <<endl;
            char ans;
            cin>>ans;

            vector<shared_ptr<StreetSquare>> allStreets = board->get_allStreets();

            if(ans == 'A'){
                cout << player->get_name() << " building an house ." << endl;
                build_house(player, street, allStreets);
            }

            if(ans == 'B'){
                cout << player->get_name() << " building an hotel ." << endl;
                build_hotel(player, street, allStreets);
            }

            else{
                //Player enter None
                cout << "You decide to not buy ." << endl;
            }
        }


        else{         
            /* Street already has an owner, then player must pay rent
            If the player cant afford the rent, definehim as bankrupt*/
            int rent = street.calc_rent();

            if(!player->can_afford(rent)){
                cout << "The player can't afford the rent price ." << endl;
                handle_nankruptcy_(player, street.get_owner());   
            }

            cout << player->get_name() << "Pay rent of :" << rent << "NIS , to " << street.get_owner()->get_name() << endl;
            player->pay_rent(street.get_owner(), rent);
        }
}




void GameManager::handle_train_landing(shared_ptr<Player> player, TrainSquare& train){

    cout << player->get_name() <<" land on Train square ." << endl;

        //In case the train has no owner
        if(!train.get_owner()){
            cout << "The amount of money you have is :" << player->get_money() <<endl;
            cout << "The train has no owner, would you like to buy it in: " << train.get_price() <<" NIS ? \n Enter: Y (for yes) or N (For no)" << endl;
            char ans;
            cin>>ans;//Get the input from the player

            if(ans == 'Y' ){
                //Player want to buy the train
                buy_train(player, train);
            }

            else{
                cout << "You decide to not buy ." <<endl;
            }

        }

        //If the owner of the train is player
        if(train.get_owner() = player){
            cout << "You are the owner of the Train . " << endl;    
        }

        else{
   
            /* The train already has an owner, then player must pay rent
            If the player cant afford the rent, define him as bankrupt*/
            int rent = train.calc_rent();
            cout << "You land on owned train, and must pay rent of :" << rent << "NIS" << endl;

            if(!player->can_afford(rent)){
                cout << "The player can't afford the rent price ." << endl;
                handle_nankruptcy_(player, train.get_owner());   
            }

            cout << player->get_name() << "Pay rent of :" << rent << "NIS , to " << train.get_owner()->get_name() << endl;
            player->pay_rent(train.get_owner(), rent);
        }

}




void GameManager::handle_company_square(shared_ptr<Player> player, CompanySquare& company, int diceRoll){

        //In case the company has no owner
        if(!company.get_owner()){
            cout << "The amount of money you have is :" << player->get_money() <<endl;
            cout << "The company has no owner, would you like to buy it in: " << company.get_price() <<" NIS ? \n Enter: Y (for yes) or N (For no)" << endl;
            char ans;
            cin>>ans;//Get the input from the player

            if(ans == 'Y' ){
                //Player want to buy the company
                buy_company(player, company);
            }

            else{
                cout << "You decide to not buy ." <<endl;
            }

        }

        //If the owner of the train is player
        if(company.get_owner() = player){
            cout << "You are the owner of the company . " << endl;    
        }

        else{
   
            /* The company already has an owner, then player must pay rent of : dice roll result*10
            If the player cant afford the rent, define him as bankrupt*/
            int rent = diceRoll*10;
            cout << "You land on owned company, and must pay rent of :" << rent << "NIS" << endl;

            if(!player->can_afford(rent)){
                cout << "The player can't afford the rent price ." << endl;
                handle_nankruptcy_(player, company.get_owner());   
            }

            cout << player->get_name() << "Pay rent of :" << rent << "NIS , to " << company.get_owner()->get_name() << endl;
            player->pay_rent(company.get_owner(), rent);
        }
}




//Handle the player's landing based on the respective square's functionality 
void GameManager::handle_player_landing(shared_ptr<Player>  player, Square& square, int diceRoll){

    if(square.get_type() == "Street Square"){
        
        StreetSquare& street = dynamic_cast<StreetSquare&>(square);
        handle_street_landing(player, street);
        return;
    }

    if(square.get_type() == "Train Square"){
        
        TrainSquare& train = dynamic_cast<TrainSquare&>(square); 
        handle_train_landing(player, train);
        return;
    }


    if(square.get_type() == "Surprise Square"){
        
        SurpriseSquare& surprise = dynamic_cast<SurpriseSquare&>(square); 
        handle_surprise_square(player, surprise);
        return;
    }


    if(square.get_type() == "Free Parking Square"){
        cout<< player->get_name() <<" land in free parking square, end's player turn. ";
        return;
    }


    if(square.get_type() == "Company Square"){
        cout<< player->get_name() <<" land in free Company square .";

        CompanySquare& company = dynamic_cast<CompanySquare&>(square); 
        handle_company_square(player, company, diceRoll);
    }



    if(square.get_type() == "Tax Square"){

        cout<< player->get_name() <<" land in free Company square .";

        TaxSquare& tax = dynamic_cast<TaxSquare&>(square); 
        
            if(!player->can_afford(tax.get_tax())){
                cout << "The player can't afford the tax price ." << endl;
                handle_nankruptcy(player);   
            }
            else{
                cout << player->get_name() << "Pay tax of : 100 NIS ." << endl;
                player->sub_money(tax.get_tax());
            }
    }


    if(square.get_type() == "Jail Square"){
        cout << player->get_name() << "land on jail square ." << endl;
    }
    
    if(square.get_type() == "Go to Jail Square"){

        cout << player->get_name() << "land on go to jail square ." << endl;
    
        //sent player to jail
        set_jail_state(player, true);
    }

    if(square.get_type() == "Start Square"){
        cout << player->get_name() << "land on Start square ." << endl;
    }


}




//Handle the surprise card functionality
void GameManager::handle_surprise_square(shared_ptr<Player> player, SurpriseSquare& surprise){
    
    //Gets a random index to dynamically select a surprise card
    size_t index = surprise.get_card_index();

    //Perform the card method
    handle_surprise_card(player, index);

}



void GameManager::handle_surprise_card(shared_ptr<Player> player, size_t index){
    cout << player->get_name() << "recive a surprise card ! (in index " << index <<")" <<endl;
    cout<< "The content of" << index <<" surprise card is :" <<endl;
        
    switch(index){
            
        case 0:
        cout <<"0. Advance to Go (Collect $200) " <<endl;
        move_player_idx(player, 0);     //Go (or Start) square index = 0
        break;


        case 1:
        cout << "1. Bank pays you dividend of $50" <<endl;
        int dollar = 4;
        int NIS_sum = dollar*50;  //change the amount to NIS
        player->add_money(NIS_sum);
        break;


        case 2:
        cout << "2. Go back 3 spaces" << endl;

        //Gets the current position of the player & the square he is on
        Square& curr_square = board->get_square_by_position(player->get_position());
        size_t new_index = (curr_square.index - 3)%40;    //go back 3 squares

        GameManager::move_player_idx(player, new_index);
        break;
        


        case 3:
        cout << "3. Go directly to Jail – do not pass Go, do not collect 200 NIS" <<endl;
        set_jail_state(player, true);
        break;


        case 4:
        cout << "4. Make general repairs on all your property – For each house pay 25 NIS – For each hotel 100 NIS"<< endl;
        int houses_price = player->houses_in_owned()*25;
        cout<< "You have " <<player->houses_in_owned() << " houses. Pay : " << houses_price << "NIS." <<endl;
        player->sub_money(houses_price);   //Pay for the houses

        int hotels_price = player->hotels_in_owned()*100;
        cout<< "You have " <<player->hotels_in_owned() << " houses. Pay : " << hotels_price << "NIS." <<endl;
        player->sub_money(hotels_price);   //Pay for the hotels
        break;


        case 5:
        cout << "5. Pay poor tax of 15 NIS" << endl;
        player->sub_money(15);
        break;


        case 6:
        cout<<"6. Take a trip to Reading Railroad – If you pass Go collect 200 NIS" <<endl;
        move_player_idx(player, 5);       //Reading Railroad square index = 5
        break;


        case 7:
        cout <<"7. Take a walk on the Boardwalk – Advance token to Boardwalk" <<endl;
        move_player_idx(player, 39);      //Boardwalk square index = 5
        break;


        case 8:
        cout <<" 8. You have been elected Chairman of the Board – Pay each player 50 NIS" <<endl;
         for(int i= 0 ; i < this->players.size() ; i++){
            if(players[i] != player){
              player->pay_rent(players[i], 50);
            }
        }
        break;


        case 9:
        cout << "9. Your building loan matures – Collect $150" <<endl;
        int dollar = 4;
        int sum = dollar*150;
        player->add_money(sum);
        break;


        case 10:
        cout<< "10. Get out of Jail Free – This card may be kept until needed or traded" <<endl;
        
        if (player->is_in_jail()) { // Check if the player is in jail
            set_jail_state(player, false);   // Get the player out of jail
        } 
        else {
            player->set_jail_card(true);     // Give the player the "Get Out of Jail Free" card
        }
        break;


        case 11:
        cout << "11. Advance to Illinois Ave. – If you pass Go, collect 200 NIS " <<endl;
        move_player_idx(player, 24);        //Illinois Ave square index = 24
        break;


        case 12:
        cout << "12. Advance to St. Charles Place – If you pass Go, collect 200 NIS" <<endl;
        move_player_idx(player, 11);        //St. Charles Place square index = 11
        break;


        case 13:
        cout << "13. You are assessed for street repairs – 40 NIS per house, 115 NIS per hotel" << endl;
        int houses_price = player->houses_in_owned()*40;
        cout<< "You have " <<player->houses_in_owned() << " houses. Pay : " << houses_price << "NIS." <<endl;
        player->sub_money(houses_price);   //Pay for the houses

        int hotels_price = player->hotels_in_owned()*115;
        cout<< "You have " <<player->hotels_in_owned() << " houses. Pay : " << hotels_price << "NIS." <<endl;
        player->sub_money(hotels_price);   //Pay for the hotels

        break;


        case 14:
        cout <<"14. Advance to Go (Collect $200) " <<endl;
        move_player_idx(player, 0);     //Go (or Start) square index = 0
        break;


        case 15:
        cout << "15.Go to Free Parking – If you pass Go, collect 200 NIS" << endl;
        move_player_idx(player, 20);      //St. Charles Place square index = 20
        break;

    }

}




//Player buy a street
void GameManager::buy_street(shared_ptr<Player> buyer, StreetSquare& street){

    if(street.get_owner() != nullptr){
        cout << "The street already has an owner ." << endl;
        return;
    }

    int streetPrice = street.get_price();

    if(!buyer->can_afford(streetPrice)){
        cout << "The buyer can't afford the street price ." << endl;
        return;
    }

    //The street doesn't have an owner and the buyer can afford the purchase
    cout << "The player pay for the street " <<endl;
    buyer->sub_money(streetPrice);  //Pay for the street
    buyer->add_street(street);      //Add the street to the buyer list of street he owned
    
    //Set the buyer to be the owner of the street
    street.set_owner(buyer);        
    cout << buyer->get_name() << "Is the owner of "<< street.streetName <<endl;

}






//Player buy a train
void GameManager::buy_train(shared_ptr<Player> buyer, TrainSquare& train){


    if(train.get_owner() != nullptr){
        cout << "The train already has an owner ." << endl;
        return;
    }

    int trainPrice = train.get_price();

    if(!buyer->can_afford(trainPrice)){
        cout << "The buyer can't afford the train price ." << endl;
        return;
    }

    //The train doesn't have an owner and the buyer can afford the purchase

    buyer->sub_money(trainPrice);  //Pay for the train
    buyer->add_train(train);      //Add the train to the buyer list of trains he owned
    
    //Set the buyer to be the owner of the train
    train.set_owner(buyer);     
    cout << buyer->get_name() << "Is the owner of the train ."<< endl;   

}
    



//Player buy a company
void GameManager::buy_company(shared_ptr<Player>  buyer, CompanySquare& company){

    //Check if the company already have an owner
    if(company.get_owner() != nullptr){
        cout << "The company already has an owner ." << endl;
        return;
    }

    int companyPrice = company.get_price();

    //Check if the buyer can afford the purchase
    if(!buyer->can_afford(companyPrice)){
        cout << "The buyer can't afford the company price ." << endl;
        return;
    }

    //The company doesn't have an owner and the buyer can afford the purchase
    //Pay for the company
    buyer->sub_money(companyPrice);  
    
    //Set the buyer to be the owner of the company
    company.set_owner(buyer);        
    cout << buyer->get_name() << "Is the owner of the company ." << endl;

}





//Player buy an house
void GameManager::build_house(shared_ptr<Player> buyer, StreetSquare& street,vector<shared_ptr<StreetSquare>> allStreets){

    //Checks whether an house can be built & the buyer is the owner of the street
    if(!street.can_build_house(buyer)){
        cout << "Can't build an house in this street. " << endl;
        return;
    }

    //Checks if the buyer have all the streets in color group -> condition for building an house
    if(!buyer->owns_all_color(street.colorGroup, allStreets)){
        cout << "The buyer dosn't have all the streets in color group ." << endl;
        return;
    }

    //Checks if the buyer can build the house in balance 
    if(!buyer->can_build_balance(street.colorGroup, allStreets)){
        cout << "The Player can't build in balance ." << endl;
        return;
    }

    //The buyer is the owner of the street & he can build an house in balance & owned all color group

    int housePrice = street.get_house_price();

    if(!buyer->can_afford(housePrice)){
        cout << "The buyer can't afforn the house price .";
        return;
    }

    //The buyer can afford the purches
    buyer->sub_money(housePrice);

    /* board->draw_house(buyer, street) --> draw the asset on board in the player color */

    street.promote_houses();
}







//Player buy an hotel
void GameManager::build_hotel(shared_ptr<Player> buyer, StreetSquare& street,vector<shared_ptr<StreetSquare>> allStreets){

    //Checks if the buyer is the the owner of the street & the street owned 4 houses in his ownership
    if(street.can_build_hotel(buyer)){
        cout << "The buyer can't build an hotel ." << endl;
    }


    int hotelPrice = street.get_hotel_price();

    if(!buyer->can_afford(hotelPrice)){
        cout << "The buyer can't afforn the hotel price .";
        return;
    }

    //The buyer can afford the purches
    buyer->sub_money(hotelPrice);

    /* board->draw_hotel(buyer, street) --> draw the asset on board in the player color */
    
    //Update the street object that hotel has been build
    street.set_hotel();

}





//----------------------------------------------Jail handling-------------------------------------------------------

void GameManager::set_jail_state(shared_ptr<Player> player, bool state){
    
    //If the player have the jail card, we don't send him to jail
    if(player->get_jail_card() && state){
        player->set_jail_card(false);    //update the card usage
        player->jail_state(false);       //Jail state of the player is false
        return;
    }

    //Set the new state
    player->jail_state(state);

    //If we set the player in jail, then move him to the jail square
    if(state && player->get_jail_card()){
        move_player_idx(player, 10);  //move the player to jail square (index 10)
    }

}



//-------------------------------------------Nankruptcy handle---------------------------------------------------




void GameManager::handle_nankruptcy(shared_ptr<Player> player){

    cout<< player->get_name() << " is bankrupt ." <<endl;

    // Handle player's properties (auction, return to the bank, etc.)
    player->clear_properties(); 

    // Remove the player from the game
    auto it = remove(this->players.begin(), this->players.end(), player);

    if (it != this->players.end()) {
        this->players.erase(it);
    }

    this->numOfPlayers--;

}



void GameManager::handle_nankruptcy_(shared_ptr<Player> bankruptPlayer, shared_ptr<Player> player){


    cout<< bankruptPlayer->get_name() << " is bankrupt ." <<endl;
    
    //All the assets of the bankrupt player is move to the player who owns the debt
    cout << "Move all assets of " << bankruptPlayer->get_name() << " to " << player->get_name() << endl;;
    bankruptPlayer->move_assets(player);

    // Remove the player from the game
    auto it = remove(this->players.begin(), this->players.end(), player);

    if (it != this->players.end()) {
        this->players.erase(it);
    }

    this->numOfPlayers--;
}




//----------------------------------------------Turn Handling-----------------------------------------------------
  
  
  
int GameManager::roll_dice() {

    cout << "Roll dices...." <<endl;
    int dice1 = rand() % 6 + 1;   // Roll first die (1 to 6)
    int dice2 = rand() % 6 + 1;   // Roll second die (1 to 6)
    cout << "The outcome of the dices roll is (" << dice1 << "," << dice2 << ")" << endl;

    if(dice1 == dice2){
    cout<< "The outcom is a double !" << endl;
        this->double_outcome = true;
        this->double_counter++;
    }

    cout << "Player need to move " << dice1 + dice2 << "steps forward" << endl;
    return dice1 + dice2;
}




void GameManager::play_turn(){

    //Get the corrent player 
    shared_ptr<Player> currPlayer = players[currPlayerIdx];
    cout << "Current player turn: " << currPlayer->get_name() << endl;

    if(currPlayer->is_in_jail()){

        if(currPlayer->turnsInJail <= 3){

            //Promote the turns the player is in jail
            currPlayer->turnsInJail++;

            cout << "The player now is in jail for "<< currPlayer->turnsInJail << " turns .";
            cout << "Promot the turn to the next player ." << endl;

            //Promote the turn to the next player
            currPlayerIdx = (currPlayerIdx + 1) % players.size();
            return;
        }

        //The player get out from jail in this turn
        else if(currPlayer->turnsInJail > 3){
            
            cout << "The player can get out of jail under this conditions :" << endl;
            cout << "Pay 50 NIS or double dice roll outcome ." << endl;
            int diceRoll = roll_dice();
                
            //Condition to get out from jail 
            if(!currPlayer->can_afford(50) && !double_outcome){
                cout << "the player can't afford the price to get out from jail and the outcome isn't double . " << endl;
                cout << "The player must leave the game" << endl;
                handle_nankruptcy(currPlayer);
            }

            if(double_outcome || currPlayer->sub_money(50)){
                cout <<"Get the player out of jail." << endl;
                set_jail_state(currPlayer, false);
            }
        }

    }

    //The corrent player isn't in jail || release now from jail
    else{
        
        //roll the dice
        int diceRoll = roll_dice();

        //move the player according to the roll dice result and handle landing
        move_player(currPlayer, diceRoll);


        if(double_counter >= 3){
            cout << "In the 3 time the outcom is double, the player sent into jail" <<endl;
            set_jail_state(currPlayer, true);

            //initilize double variables
            double_counter = 0;
            double_outcome = false;
        }

        if(double_outcome && double_counter != 3){
            cout <<"Another turn for the current player, as couse of double outcom !" << endl;
            double_counter++;
            cout << currPlayer->get_name() <<" entitled to another turn ." << endl;
        }

        else{
            cout <<"Promote the corrent player index ." <<endl;
            currPlayerIdx = (currPlayerIdx + 1) % players.size();
        }
    }

}




bool GameManager::is_over(){

bool win = false;
shared_ptr<Player> winner;

    //Player win if he is the only one that left in the game
    if(this->players.size() ==1){
        win = true;
        announce_winner(players[0]);
    }

    //Player win if he have 4000 amount of money
    for( auto player : this->players){

        if(player->get_money() >= 4000){
            winner = player;
            win = true;
            announce_winner(player);
        }
    }
    
return win;
}



void GameManager::announce_winner(shared_ptr<Player> player){
    cout << player->get_name() << " is the winner of the game !" <<endl;

    players.clear();
}



//-------------------------------------------Game initilization-----------------------------------------------------

sf::Vector2f GameManager::get_start_position(int index){

    //Define the position
    sf::Vector2f player1(900.f, 860.f);
    sf::Vector2f player2(900.f, 880.f);
    sf::Vector2f player3(900.f, 900.f);
    sf::Vector2f player4(900.f, 930.f);
    sf::Vector2f player5(950.f, 860.f);
    sf::Vector2f player6(950.f, 880.f);
    sf::Vector2f player7(950.f, 900.f);
    sf::Vector2f player8(950.f, 930.f);


    switch (index) {
        case 1:
            return player1;
            
        case 2:
            return player2;

        case 3:
            return player3;

        case 4:
            return player4;

        case 5:
            return player5;

        case 6:
            return player6;

        case 7:
            return player7;

        case 8:
            return player8;

        default:
            return; // Handle invalid index
}
}


void GameManager::initialize_players(int numOfPlayers, sf::RenderWindow& window){

    for(int i = 1 ; i <= numOfPlayers ; i++){
        string name = "Player " + to_string(i);   //Name of the player is by his index

        shared_ptr<Player> player = make_shared<Player>(name, 1500);      //Initilize the player object 
        player->init_player_vis(this->obj.get_path_by_idx(i) ,window);
        players.push_back(player);
        player->set_position(get_start_position(i));  //locat player on board
    }

}




//Initilize and draw the players on the board, the board – on the given window
void GameManager::initialize_game(sf::RenderWindow& window ){

    //Creats / get the instance of the board 
    board->get_instance();

    //Draw the board on the given window
    board->render(window);

}




void GameManager::start_game(sf::RenderWindow& gameWindow){

    cout << "Please enter the number of players :" << endl;
    cin >> this->numOfPlayers;

    // Initilize the player object & the game board
    initialize_game(gameWindow);
    initialize_players(this->numOfPlayers, gameWindow);

}
