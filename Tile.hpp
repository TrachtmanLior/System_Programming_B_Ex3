// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#ifndef TILE_HPP
#define TILE_HPP

#include <vector>
#include <utility> // For std::pair
#include "Resources.hpp"

namespace ariel {

    class Tile {
    private:
        int id;                                 // Unique identifier for the tile
        std::vector<int> vertices;              // Vertices associated with the tile
        Resources::ResourceType type;           // Type of resource provided by the tile
        std::vector<std::pair<int, int>> edges; // Edges connecting vertices, defined by pairs of vertex indices
        int diceNumber;                         // Number on the dice that activates this tile

    public:
        // Constructor: initializes a tile with specified attributes
        Tile(int id, std::vector<int> vertices, Resources::ResourceType type, int diceNumber);

        // Getter functions to retrieve tile attributes
        int getId() const;                                          // Returns the tile's ID
        std::vector<int> getVertices() const;                       // Returns the vertices associated with the tile
        Resources::ResourceType getType() const;                    // Returns the type of resource the tile provides
        int getdiceNumber() const;                                  // Returns the dice number associated with the tile

        // Setter functions to modify tile attributes
        void setVertices(const std::vector<int>& vertices);         // Sets the vertices associated with the tile
        void setType(Resources::ResourceType type);                 // Sets the type of resource the tile provides
        void setdiceNumber(int diceNumber);                         // Sets the dice number associated with the tile

        // Getter function to retrieve edges connecting vertices
        std::vector<std::pair<int, int>> getEdges() const;          // Returns the edges connecting vertices
    };

} // namespace ariel

#endif // TILE_HPP
