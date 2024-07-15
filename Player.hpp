// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include "Board.hpp"
#include "Settlement.hpp"
#include "DevelopmentCard.hpp"
#include "Road.hpp"
#include "Resources.hpp"

namespace ariel {
    class Board; // Forward declaration of Board class

    class Player {
    private:
        std::string playerId; // Unique identifier for the player
        int points; // Player's total points
        int knights; // Number of knight cards owned by the player
        int turnsPlayed; // Number of turns this player has played
        bool roadBuildingCardActivated; // Flag indicating if the road building card is activated
        bool hasLargestArmy; // Flag indicating if the player has the largest army
        std::vector<Player> players; // Vector of all players in the game
        std::vector<Road> roads; // Vector of roads owned by the player
        std::vector<DevelopmentCard> developmentCards; // Vector of development cards owned by the player
        std::vector<std::pair<Resources::ResourceType, int>> resources; // Vector of resources owned by the player
        static Player* currentPlayer; // Pointer to track the current player's turn
        static Player* playerWithLargestArmy; // Pointer to the player with the largest army

    public:
        Player(const std::string& playerId); // Constructor to initialize a player with a given playerId
        std::vector<Player> getPlayers(); // Getter for the vector of all players in the game
        void setPlayers(Player& player); // Setter to add a player to the vector of all players
        void placeSettlement(int vertice, Board& board); // Method to place a settlement on a vertex of the board
        void placeRoad(int fromVertice, int toVertice, Board& board); // Method to place a road between two vertices of the board
        void rollDice(Board& board); // Method for the player to roll the dice and take actions based on the roll
        void trade(Player& other, const std::string& giveResource, const std::string& getResource, int giveAmount, int getAmount, Board& board); // Method for the player to trade resources with another player
        void printPoints() const; // Method to print the player's current points
        std::string getName() const; // Getter for the player's identifier
        int getPoints() const; // Getter for the player's total points
        void setPoints(int); // Setter for the player's total points
        int getKnights(); // Getter for the number of knight cards owned by the player
        bool getHasLargestArmy(); // Getter for whether the player has the largest army
        void setKnights(int num); // Setter for the number of knight cards owned by the player
        bool placeCity(int vertice, Board& board); // Method to place a city on a vertex of the board
        bool hasResourcesForRoadBuilding() const; // Method to check if the player has enough resources to build a road
        bool hasResourcesForCityBuilding() const; // Method to check if the player has enough resources to build a city
        bool hasResourcesForSettlementBuilding() const; // Method to check if the player has enough resources to build a settlement
        bool hasResourcesForDevelopmentCard() const; // Method to check if the player has enough resources to buy a development card
        void removeResourcesForRoadBuilding(); // Method to remove resources from the player's inventory for building roads
        void removeResourcesForCityBuilding(); // Method to remove resources from the player's inventory for building cities
        void removeResourcesForSettlementBuilding(); // Method to remove resources from the player's inventory for building settlements
        void removeResourcesForDevelopmentCard(); // Method to remove resources from the player's inventory for buying a development card
        void buyDevelopmentCard(Board& board); // Method for the player to buy a development card from the board's deck
        bool hasDevelopmentCard(); // Method to check if the player has any development cards
        void playDevelopmentCard(DevelopmentCardType cardType, Board& board); // Method for the player to play a development card they own
        void addResource(Resources::ResourceType resource, int quantity, Board& board); // Method to add a resource to the player's inventory
        void drawTwoResourceCards(Board& board); // Method for the player to draw two resource cards from the board
        void claimAllResourceCards(Board& board); // Method for the player to claim all resource cards of a specific type from the board
        int getResourceCount(Resources::ResourceType resourceType) const; // Getter for the count of a specific type of resource owned by the player
        void removeResource(Resources::ResourceType resourceType, int quantity, Board& Board); // Method to remove a specified quantity of a resource from the player's inventory
        void incrementTurnsPlayed(); // Method to increment the number of turns played by the player
        void printStats(Board& board) const; // Method to print statistics and details about the player's current state
        int getTotalResources(); // Getter for the total count of all resources owned by the player
        void loseHalfResources(); // Method for the player to lose half of their resources due to an event
        void checkLargestArmy(Board& board); // Method to check if the player has achieved the largest army status
    };

}

#endif // PLAYER_HPP
