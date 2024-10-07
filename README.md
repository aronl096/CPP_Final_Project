# CPP_Final_Project

# Monopoly Game in C++

## Overview
This project is a version of the classic board game **Monopoly**, designed for 2 to 8 players. The game is implemented in C++ using the SFML library for graphical representation and terminal printing for game flow and player choices.

## Table of Contents
- [File Structure](#file-structure)
- [Game Rules](#game-rules)
- [Board Slots](#board-slots)
- [Classes and Hierarchy](#classes-and-hierarchy)
- [Roles of Each Class](#roles-of-each-class)
- [Gameplay Flow](#gameplay-flow)
- [Getting Started](#getting-started)

## File Structure
The project consists of the following files:

- **Board.cpp / Board.hpp**: Contains the implementation and declaration of the board structure and its functionalities.
- **Player.cpp / Player.hpp**: Manages player properties, money, and actions throughout the game.
- **Square.hpp**: The parent class for all square types, serving as a factory for creating square objects.
- **StreetSquare.cpp / StreetSquare.hpp**: Implements the properties and methods for street squares.
- **UtilitySquare.hpp**: Declares the functionality for utility squares.
- **SpecialSquare.cpp / SpecialSquare.hpp**: Implements the functionalities for special squares.
- **GUI_Manager.hpp / GUI_Manager.cpp**: Handles the graphical interface, drawing the board and managing house building.
- **GameManager.cpp / GameManager.hpp**: Contains the game logic, turns, and overall game flow management.
- **MonopolyGame.cpp**: The main function that initiates the game loop.

## Game Rules
Monopoly is played on a board with 40 squares where players can buy, trade, and develop properties. The game consists of various property types, including streets, trains, and special squares.

### The Game Board
The board contains different types of squares, each allowing players to perform unique actions. The dynamics of the board can accommodate additional squares as required.

### Square Types
- **Street Squares**: Belong to color groups and have associated properties like purchase price and rental costs.
- **Train Squares**: Provide income based on the number of trains owned by the player.
- **Special Squares**: Include options like "Free Parking," "Go to Jail," and various utilities.

## Classes and Hierarchy
The game structure utilizes an object-oriented approach, with a base class and multiple derived classes to represent different types of squares.

### Class Hierarchy
- **Square** (Base Class)
  - **StreetSquare**
  - **UtilitySquare**
    - **TrainSquare**
    - **JailSquare**
    - **TaxSquare**
    - **FreeParkingSquare**
    - **GoToJailSquare**
    - **CompanySquare**
  - **SpecialSquare**
    - **SurpriseSquare**

## Roles of Each Class
- **Square**: The parent class for all squares, providing a common interface for derived classes.
- **StreetSquare**: Represents properties that players can buy and develop, with rental costs based on the number of houses/hotels.
- **TrainSquare**: Represents train properties, calculating tax based on the number of trains owned.
- **SpecialSquare**: Implements unique functionalities for various special squares on the board.
- **GUI_Manager**: Responsible for graphical representation of the game board and managing player interactions visually.
- **GameManager**: Central class handling the overall game flow, player turns, and rule enforcement.
- **Player**: Represents each player in the game, managing their resources and actions.

## Gameplay Flow
1. Each player starts with 1500 currency.
2. Players take turns rolling two dice and moving around the board.
3. Depending on the square landed on, players can buy properties, pay rent, or perform special actions.
4. Players can build houses and hotels following specific rules related to property ownership.
5. The game continues until one player achieves victory conditions, either by bankrupting all opponents or accumulating sufficient wealth.

## Getting Started
To run the game, ensure you have the necessary dependencies installed, including SFML. Compile the project using your preferred C++ compiler and execute the `MonopolyGame` binary.

### Compilation
```bash
make
```

### Running the Game
```bash
./MonopolyGame
```
