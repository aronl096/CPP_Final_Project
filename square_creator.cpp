#include "SquareFactory.hpp"


    // Create in runtime the requested square
    Square* SquareFactory::create_square(const std::string& type, int index, sf::FloatRect square_area, std::vector<std::string> extra_args) {
        if (type == "Street Square" && extra_args.size() >= 2) {
            return new StreetSquare(type, index, square_area, extra_args[0], extra_args[1]);
        }

        if (type == "Train Square") {
            return new TrainSquare(type, index, square_area);
        }

        if (type == "Jail Square") {
            return new JailSquare(type, index, square_area);
        }

        if (type == "Start Square") {
            return new StartSquare(type, index, square_area);
        }

        if (type == "Go To Jail Square") {
            return new GoToJailSquare(type, index, square_area);
        }

        if (type == "Surprise Square") {
            return new SurpriseSquare(type, index, square_area);
        }

        if (type == "Tax Square") {
            return new TaxSquare(type, index, square_area);
        }

        if (type == "Free Parking Square") {
            return new FreeParkingSquare(type, index, square_area);
        }

        if (type == "Company Square") { // Fixed typo here
            return new CompanySquare(type, index, square_area);
        }

        if(type == "Community Chest Square"){
            return new CommunityChestSquare(type, index, square_area);
        }

        std::cerr << "Failed to recognize the kind of square." << std::endl; // Changed to std::cerr for error messages
        return nullptr;
    }
