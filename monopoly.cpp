#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"



int main() {


    // Open SFML window
    sf::RenderWindow window(sf::VideoMode(1020, 950), "Monopoly Game");

    GameManager game;

    // Run the program as long as the window is open
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear the window
        window.clear(sf::Color::White); // Set the background color or texture here

        // Initialize players & board (only done once)
        if (!game.gameStarted) {
            game.start_game(window);
        }

        // Main game loop
        while (!game.is_over()) {
            // Play a turn
            game.play_turn();

            // Display the updated content
            window.display();
        }

    }

    return 0;
}
