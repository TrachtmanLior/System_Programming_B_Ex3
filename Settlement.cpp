// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#include "Settlement.hpp"
#include "Player.hpp"
#include <iostream>
#include <algorithm>

namespace ariel {

    Settlement::Settlement(std::string playerId, std::vector<std::vector<int>>& vertextoTiles, int verticeId)
        : playerId(playerId), vertextoTiles(vertextoTiles), verticeId(verticeId) {}
    // Constructor to initialize playerId, vertextoTiles, and verticeId

    std::string Settlement::getPlayerId() const {
        return playerId;
    }
    // Getter function for playerId

    int Settlement::getVerticeId() const {
        return verticeId;
    }
    // Getter function for verticeId

    void Settlement::placeSettlement() {
        // Check if verticeId is valid
        if (verticeId < 0 || (size_t)verticeId >= vertextoTiles.size()) {
            std::cerr << "Invalid verticeId!" << std::endl;
            return;
        }

        // Place the settlement
        vertextoTiles[verticeId].push_back(1); // Assuming '1' indicates the presence of a settlement
        std::cout << "Settlement placed by player " << playerId << " at vertice " << verticeId << std::endl;
    }
    // Method to place the settlement on the specified vertice

    bool Settlement::isCity() {
        return cityStatus;
    }
    // Method to check if the settlement has been upgraded to a city

    void Settlement::upgradeToCity() {
        this->cityStatus = true;
    }
    // Method to upgrade the settlement to a city

} // namespace ariel
