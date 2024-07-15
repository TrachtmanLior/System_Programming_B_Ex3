// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#ifndef SETTLEMENT_HPP
#define SETTLEMENT_HPP

#include <string>
#include <vector>

namespace ariel {

    // Forward declaration of Player and Board to avoid circular dependency
    class Player;
    class Board;

    class Settlement {
    private:
        std::string playerId; // Player ID who owns the settlement
        std::vector<std::vector<int>>& vertextoTiles; // Reference to the 2D vector representing tiles
        int verticeId; // ID of the vertex where the settlement is placed
        bool cityStatus = false; // Flag indicating if the settlement has been upgraded to a city

    public:
        Settlement(std::string playerId, std::vector<std::vector<int>>& vertextoTiles, int verticeId);
        // Constructor to initialize playerId, vertextoTiles, and verticeId

        std::string getPlayerId() const; // Getter function for playerId

        int getVerticeId() const; // Getter function for verticeId

        void placeSettlement(); // Method to place the settlement on the specified vertice

        bool isCity(); // Method to check if the settlement has been upgraded to a city

        void upgradeToCity(); // Method to upgrade the settlement to a city
    };

} // namespace ariel

#endif // SETTLEMENT_HPP
