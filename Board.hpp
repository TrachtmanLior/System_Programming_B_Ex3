// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>
#include <map>
#include "Player.hpp"
#include "Tile.hpp"
#include "Settlement.hpp"
#include "Road.hpp"
#include "DevelopmentCard.hpp"

namespace ariel {
    class Board {
    private:
        std::vector<Player> players;                        // Vector to store players in the game
        std::vector<Settlement> settlements;                // Vector to store settlements on the board
        std::vector<Road> roads;                            // Vector to store roads on the board
        std::vector<Tile> tiles;                            // Vector to store tiles on the board
        std::vector<std::vector<int>> vertextoTiles;        // 2D vector mapping vertices to tiles
        std::vector<DevelopmentCard> developmentCardDeck;   // Deck of development cards
        std::vector<DevelopmentCard> developmentCardDiscardPile; // Discard pile for development cards

    public:
        Board();                                            // Constructor for Board class
        void makeBoard();                                   // Initializes the board with tiles and vertices
        void placeSettlement(const std::string& playerId, int vertice);  // Places a settlement on a vertex for a player
        bool isSettlementAvailable(const std::string& playerName, int vertice) const;  // Checks if a settlement can be placed on a vertex
        void placeRoad(const std::string& playerId, int fromVertice, int toVertice);  // Places a road between two vertices for a player
        bool isRoadAvailable(const std::string& playerName, int fromVertice, int toVertice);  // Checks if a road can be placed between two vertices
        void initializeDevelopmentCardDeck();               // Initializes the deck of development cards
        void shuffleDevelopmentCardDeck();                  // Shuffles the development card deck
        DevelopmentCard drawDevelopmentCard();              // Draws a development card from the deck
        std::vector<Settlement>& getSettlements();          // Returns a reference to the vector of settlements
        std::vector<Road>& getRoads();                      // Returns a reference to the vector of roads
        std::vector<std::vector<int>>& getVertexToTiles();  // Returns a reference to the 2D vector mapping vertices to tiles
        Tile& getTileAtIndex(int tileId);                   // Returns a reference to the tile at a specific index
        int getNumSettlements(const std::string& player);   // Returns the number of settlements owned by a player
        int getNumRoads(const std::string& player);         // Returns the number of roads owned by a player
        void printAllTiles() const;                         // Prints information about all tiles on the board
        void printTilesAroundSettlement(const Settlement& settlement) const;  // Prints information about tiles around a settlement
        void printAllTilesInfo() const;                     // Prints detailed information about all tiles on the board
        std::vector<int> getTilesAroundSettlement(const Settlement& settlement) const;  // Returns vertices adjacent to a settlement
        void updatePlayer(Player& updatedPlayer);     // Updates player information on the board
        void addPlayer(Player& player);                     // Adds a player to the game
        std::vector<Player>& getPlayers();                  // Returns a reference to the vector of players
        void resetGame();                                   // Resets the game state
    };
}

#endif // BOARD_HPP
