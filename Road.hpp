// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#ifndef ROAD_HPP
#define ROAD_HPP

#include <utility> // For std::pair
#include <string> // For std::string

namespace ariel {

    class Road {
    private:
        std::pair<int, int> vertices; // Starting and ending vertices of the road
        std::string playerId; // Player who owns the road

    public:
        // Constructor to initialize playerId and vertices
        Road(const std::string& playerId, const std::pair<int, int>& vertices);

        // Getter function to retrieve the vertices of the road
        std::pair<int, int> getVertices() const;

        // Getter function to retrieve the player ID associated with the road
        std::string getPlayerId() const;
    };

} // namespace ariel

#endif // ROAD_HPP
