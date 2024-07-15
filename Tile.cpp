// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#include "Tile.hpp"
#include <iostream>

namespace ariel {

    Tile::Tile(int id, std::vector<int> vertices, Resources::ResourceType resourceType, int diceNumber)
        : id(id), vertices(vertices), type(resourceType), diceNumber(diceNumber) {
            // Initialize edges based on the specified vertices
            switch (id) {
                case 0:
                    edges = { {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0} };
                    break;
                case 1:
                    edges = { {6, 5}, {5, 4}, {4, 9}, {9, 8}, {8, 7}, {7, 6} };
                    break;
                case 2:
                    edges = { {10, 7}, {7, 8}, {8, 13}, {13, 12}, {12, 11}, {11, 10} };
                    break;
                case 3:
                    edges = { {12, 13}, {13, 14}, {14, 15}, {15, 16}, {16, 17}, {17, 12} };
                    break;
                case 4:
                    edges = { {8, 9}, {9, 19}, {19, 18}, {18, 14}, {14, 13}, {13, 8} };
                    break;
                case 5:
                    edges = { {4, 3}, {3, 21}, {21, 20}, {20, 19}, {19, 9}, {9, 4} };
                    break;
                case 6:
                    edges = { {2, 24}, {24, 23}, {23, 22}, {22, 21}, {21, 3}, {3, 2} };
                    break;
                case 7:
                    edges = { {23, 25}, {25, 26}, {26, 27}, {27, 28}, {28, 22}, {22, 23} };
                    break;
                case 8:
                    edges = { {21, 22}, {22, 28}, {28, 29}, {29, 30}, {30, 20}, {20, 21} };
                    break;
                case 9:
                    edges = { {19, 20}, {20, 30}, {30, 31}, {31, 32}, {32, 18}, {18, 19} };
                    break;
                case 10:
                    edges = { {14, 18}, {18, 32}, {32, 33}, {33, 34}, {34, 15}, {15, 14} };
                    break;
                case 11:
                    edges = { {16, 15}, {15, 34}, {34, 35}, {35, 36}, {36, 37}, {37, 16} };
                    break;
                case 12:
                    edges = { {34, 33}, {33, 40}, {40, 39}, {39, 38}, {38, 35}, {35, 34} };
                    break;
                case 13:
                    edges = { {32, 31}, {31, 42}, {42, 41}, {41, 40}, {40, 33}, {33, 32} };
                    break;
                case 14:
                    edges = { {30, 29}, {29, 44}, {44, 43}, {43, 42}, {42, 31}, {31, 30} };
                    break;
                case 15:
                    edges = { {28, 27}, {27, 46}, {46, 45}, {45, 44}, {44, 29}, {29, 28} };
                    break;
                case 16:
                    edges = { {44, 45}, {45, 47}, {47, 48}, {48, 49}, {49, 43}, {43, 44} };
                    break;
                case 17:
                    edges = { {42, 43}, {43, 49}, {49, 50}, {50, 51}, {51, 41}, {41, 42} };
                    break;
                case 18:
                    edges = { {40, 41}, {41, 51}, {51, 52}, {52, 53}, {53, 39}, {39, 40} };
                    break;
                default:
                    // Handle invalid id
                    std::cerr << "Invalid tile id!" << std::endl;
                    break;
            }
        }

    // Getter functions
    int Tile::getId() const {
        return id;
    }

    std::vector<int> Tile::getVertices() const {
        return vertices;
    }

    Resources::ResourceType Tile::getType() const {
        return type;
    }

    int Tile::getdiceNumber() const {
        return diceNumber;
    }

    // Setter functions
    void Tile::setVertices(const std::vector<int>& vertices) {
        this->vertices = vertices;
    }

    void Tile::setType(Resources::ResourceType type) {
        this->type = type;
    }

    void Tile::setdiceNumber(int diceNumber) {
        this->diceNumber = diceNumber;
    }

    // Getter function for edges
    std::vector<std::pair<int, int>> Tile::getEdges() const {
        return edges;
    }

}
