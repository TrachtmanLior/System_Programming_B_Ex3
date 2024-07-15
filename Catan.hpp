// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#ifndef CATAN_HPP
#define CATAN_HPP

#include <iostream>
#include <vector>
#include "Player.hpp"
#include "Board.hpp"

namespace ariel {
    class Catan {
    private:
        Board board;                // The game board
        int currentPlayerIndex;     // Index of the current player
        int currentTurn;            // Current turn number
        size_t finishedPlayersCount;// Number of players who have finished their turns
        bool gameStarted;           // Flag to check if the game has started
        bool gameEnded;             // Flag to check if the game has ended

    public:
        Catan();                    // Constructor to initialize the game
        void run();                 // Function to start running the game
        void setupGame();           // Function to set up the game before it starts
        void playTurn();            // Function to play a single turn
        void handleTurn(Player& player);  // Function to handle a player's turn
        void printGameStatus();     // Function to print the current game status
        bool checkGameEnd();        // Function to check if the game has ended
        void handleTrade(Player& currentPlayer); // Function to handle trading between players
        int getCurrentTurn();       // Getter for the current turn number
        int getCurrentPlayerIndex(); // Getter for the index of the current player
        Board& getBoard();          // Getter for the game board
        bool isGameStarted();       // Function to check if the game has started
    };
}
#endif // CATAN_HPP
