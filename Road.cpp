// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#include "Road.hpp"

namespace ariel {

    // Constructor initializing playerId and vertices
    Road::Road(const std::string& playerId, const std::pair<int, int>& vertices)
        : vertices(vertices), playerId(playerId) {
        // Corrected initializer list order for vertices and playerId
    }

    // Getter function to retrieve the vertices of the road
    std::pair<int, int> Road::getVertices() const {
        return vertices;
    }

    // Getter function to retrieve the player ID associated with the road
    std::string Road::getPlayerId() const {
        return playerId;
    }

} // namespace ariel
