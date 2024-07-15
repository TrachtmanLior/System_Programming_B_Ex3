// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#include "Catan.hpp"
#include <limits>
#include "Player.hpp"
#include "Board.hpp"
#include "DevelopmentCard.hpp"

namespace ariel {

    // Constructor to initialize Catan game
    Catan::Catan() : board(), currentPlayerIndex(0), currentTurn(1), gameStarted(false), gameEnded(false) {}

    // Function to start and run the Catan game
    void Catan::run() {
        setupGame(); // Set up the game

        while (!gameEnded) {
            playTurn(); // Play each turn until game ends
            gameEnded = checkGameEnd(); // Check if game has ended after each turn
        }

        std::cout << "Game over!\n";
        printGameStatus(); // Print final game status
    }

    // Function to set up the initial state of the game
    void Catan::setupGame() {
        std::cout << "Welcome to Catan!\n";

        // Create 4 players
        Player player1("Player1");
        Player player2("Player2");
        Player player3("Player3");
        Player player4("Player4");

        // Add players to the board
        board.addPlayer(player1);
        board.addPlayer(player2);
        board.addPlayer(player3);
        board.addPlayer(player4);

        // Reset game state
        currentPlayerIndex = 0;
        currentTurn = 1;
        gameStarted = true;
        board.makeBoard(); // Initialize the game board
    }

    // Function to play a single turn of the game
    void Catan::playTurn() {
        Player& currentPlayer = board.getPlayers()[currentPlayerIndex];
        std::cout << "It's " << currentPlayer.getName() << "'s turn.\n";

        if (currentTurn == 1) {
            // First turn: Place first settlement and road
            bool settlementPlaced = false;
            int vertice, toVertice;
            while (!settlementPlaced) {
                std::cout << "Choose where to place your first settlement on the board.\n";
                std::cin >> vertice;
                if (board.isSettlementAvailable(currentPlayer.getName(), vertice)) {
                    currentPlayer.placeSettlement(vertice, board);
                    settlementPlaced = true;
                } else {
                    std::cout << "Invalid settlement location. Please try again.\n";
                }
            }

            bool roadPlaced = false;
            while (!roadPlaced) {
                std::cout << "From the settlement, choose where to place your first road on the board.\n";
                std::cin >> toVertice;
                if (board.isRoadAvailable(currentPlayer.getName(), vertice, toVertice)) {
                    currentPlayer.placeRoad(vertice, toVertice, board);
                    roadPlaced = true;
                } else {
                    std::cout << "Invalid road location. Please try again.\n";
                }
            }

            board.updatePlayer(currentPlayer);
        } else if (currentTurn == 2) {
            // Second turn: Place second settlement and road
            bool settlementPlaced = false;
            int vertice, toVertice;
            while (!settlementPlaced) {
                std::cout << "Choose where to place your second settlement on the board.\n";
                std::cin >> vertice;
                if (board.isSettlementAvailable(currentPlayer.getName(), vertice)) {
                    currentPlayer.placeSettlement(vertice, board);
                    settlementPlaced = true;
                } else {
                    std::cout << "Invalid settlement location. Please try again.\n";
                }
            }

            bool roadPlaced = false;
            while (!roadPlaced) {
                std::cout << "From the settlement, choose where to place your second road on the board.\n";
                std::cin >> toVertice;
                if (board.isRoadAvailable(currentPlayer.getName(), vertice, toVertice)) {
                    currentPlayer.placeRoad(vertice, toVertice, board);
                    roadPlaced = true;
                } else {
                    std::cout << "Invalid road location. Please try again.\n";
                }
            }

            board.updatePlayer(currentPlayer);
        } else {
            // Subsequent turns: Normal turn gameplay
            handleTurn(currentPlayer); // Handle player's turn actions
            board.updatePlayer(currentPlayer);
        }

        currentPlayer.incrementTurnsPlayed(); // Increment turns played counter for the current player

        // Check if all players have finished their turns
        if (finishedPlayersCount == board.getPlayers().size()) {
            finishedPlayersCount = 0;
            currentTurn++;
        }

        finishedPlayersCount++;

        // Move to the next player for the next turn
        currentPlayerIndex = (currentPlayerIndex + 1) % board.getPlayers().size();
    }

    // Function to handle a player's turn actions
    void Catan::handleTurn(Player& currentPlayer) {
        // Display main menu options for the current player
        std::cout << "Options for " << currentPlayer.getName() << ":\n";
        std::cout << "1. Roll dice\n";
        if (currentPlayer.hasDevelopmentCard()) {
            std::cout << "2. Use development card\n";
        }
        std::cout << "10. Instant win\n";
        std::cout << "11. Give 50 resources\n";

        int choice;
        std::cin >> choice;

        // Handle player's menu choices
        if (choice == 1) {
            // Player chose to roll dice
            currentPlayer.rollDice(board); // Roll dice and update resources
            board.updatePlayer(currentPlayer);
            currentPlayer.printStats(board); // Print player's statistics

            bool turnComplete = false;
            while (!turnComplete) {
                std::cout << "3. Build road\n";
                std::cout << "4. Build settlement\n";
                std::cout << "5. Build city\n";
                std::cout << "6. Buy development card\n";
                std::cout << "7. Use development card\n";
                std::cout << "8. Trade with another player\n";
                std::cout << "9. End turn\n";

                std::cin >> choice;
                int vertice;

                switch (choice) {
                    case 3:
                        std::cout << "Choose where to place your road from on the board.\n";
                        int fromVertice;
                        std::cin >> fromVertice;
                        std::cout << "Choose where to place your road to on the board.\n";
                        int toVertice;
                        std::cin >> toVertice;
                        currentPlayer.placeRoad(fromVertice, toVertice, board);
                        board.updatePlayer(currentPlayer);
                        break;
                    case 4:
                        std::cout << "Choose where to place your settlement on the board.\n";
                        std::cin >> vertice;
                        currentPlayer.placeSettlement(vertice, board);
                        board.updatePlayer(currentPlayer);
                        break;
                    case 5:
                        std::cout << "Choose where to place your city on the board.\n";
                        std::cin >> vertice;
                        currentPlayer.placeCity(vertice, board);
                        board.updatePlayer(currentPlayer);
                        break;
                    case 6:
                        currentPlayer.buyDevelopmentCard(board);
                        board.updatePlayer(currentPlayer);
                        break;
                    case 7:
                        if (currentPlayer.hasDevelopmentCard()) {
                            std::cout << "Choose which development card you want to play:\n";
                            std::string card;
                            std::cin >> card;
                            // Check if the input is a valid card
                            if (DevelopmentCard::isValidDevelopmentCardType(card)) {
                                currentPlayer.playDevelopmentCard(DevelopmentCard::stringToDevelopmentCardType(card), board);
                                turnComplete = true; // End the turn after using a development card
                                board.updatePlayer(currentPlayer);
                            } else {
                                std::cout << "Invalid card type. Please enter a valid development card.\n";
                            }
                        } else {
                            std::cout << "You don't have any development cards.\n";
                        }
                        break;
                    case 8:
                        handleTrade(currentPlayer); // Initiate trade with another player
                        board.updatePlayer(currentPlayer);
                        break;
                    case 9:
                        turnComplete = true; // End turn
                        board.updatePlayer(currentPlayer);
                        break;
                    default:
                        std::cout << "Invalid choice. Please enter a valid option.\n";
                        break;
                }
            }
        } else if (choice == 2 && currentPlayer.hasDevelopmentCard()) {
            // Player chose to use development card
            currentPlayer.printStats(board);
            std::cout << "Choose which development card you want to play:\n";
            std::string card;
            std::cin >> card;
            // Check if the input is a valid card
            if (DevelopmentCard::isValidDevelopmentCardType(card)) {
                currentPlayer.playDevelopmentCard(DevelopmentCard::stringToDevelopmentCardType(card), board);
                board.updatePlayer(currentPlayer);
            } else {
                std::cout << "Invalid card type. Please enter a valid development card.\n";
            }
        } else if (choice == 10) {
            // Instant win
            currentPlayer.setPoints(10); // Assuming setPoints function exists
            std::cout << currentPlayer.getName() << " wins the game with 10 points!\n";
            board.updatePlayer(currentPlayer);
        } else if (choice == 11) {
            // Give 50 resources
            std::cout << "Choose the type of resource to receive 50 of ('Brick', 'Wood', 'Wool', 'Grain', 'Ore'):\n";
            std::string resource;
            std::cin >> resource;
            currentPlayer.addResource(Resources::stringToResourceType(resource), 50, board);
            board.updatePlayer(currentPlayer);
            handleTurn(currentPlayer); // Recursive call to handle additional turn actions
        } else {
            // Invalid choice or trying to roll dice again
            std::cout << "Enter a valid choice.\n";
            handleTurn(currentPlayer); // Recursive call to restart the turn, preserving the diceRolled flag
            board.updatePlayer(currentPlayer);
        }
    }

    // Print the points of all players in the game
    void Catan::printGameStatus() {
        for (const Player& player : board.getPlayers()) {
            player.printPoints(); // Print each player's points
        }
    }

    // Check if any player has reached 10 points, indicating game end
    bool Catan::checkGameEnd() {
        for (const Player& player : board.getPlayers()) {
            if (player.getPoints() >= 10) {
                std::cout << player.getName() << " has reached 10 points. Game ends.\n";
                return true; // Return true if any player has 10 or more points
            }
        }
        return false; // Return false if no player has 10 points
    }

    // Handle trading between the current player and another player
    void Catan::handleTrade(Player& currentPlayer) {
        std::cout << "Choose the player you want to trade with:\n";
        for (size_t i = 0; i < board.getPlayers().size(); ++i) {
            if (&board.getPlayers()[i] != &currentPlayer) {
                std::cout << i + 1 << ". " << board.getPlayers()[i].getName() << "\n";
            }
        }

        size_t otherPlayerIndex;
        std::cin >> otherPlayerIndex;
        --otherPlayerIndex; // Adjust for 0-based indexing

        if (otherPlayerIndex >= board.getPlayers().size() || &board.getPlayers()[otherPlayerIndex] == &currentPlayer) {
            std::cout << "Invalid player selected.\n";
            return; // Check for valid player selection
        }

        Player& otherPlayer = board.getPlayers()[otherPlayerIndex];

        currentPlayer.printStats(board); // Print current player's stats
        std::cout << "\n\n";
        otherPlayer.printStats(board); // Print other player's stats
        std::cout << "\n\n";

        // Prompt and handle trade inputs
        std::cout << "Enter the resource or development card you want to give:\n";
        std::string giveItem;
        std::cin >> giveItem;

        std::cout << "Enter the amount you want to give:\n";
        int giveAmount;
        std::cin >> giveAmount;

        std::cout << "Enter the resource or development card you want to get:\n";
        std::string getItem;
        std::cin >> getItem;

        std::cout << "Enter the amount you want to get:\n";
        int getAmount;
        std::cin >> getAmount;

        currentPlayer.trade(otherPlayer, giveItem, getItem, giveAmount, getAmount, board); // Initiate trade between players
    }

    // Getter for the current turn number
    int Catan::getCurrentTurn() {
        return currentTurn;
    }

    // Getter for the index of the current player
    int Catan::getCurrentPlayerIndex() {
        return currentPlayerIndex;
    }

    // Getter for the game board
    Board& Catan::getBoard() {
        return board;
    }

    // Getter for the game start status
    bool Catan::isGameStarted(){
        return gameStarted;
    }
}