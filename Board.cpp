// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#include "Board.hpp"
#include "Resources.hpp"
#include "Player.hpp"
#include "Settlement.hpp"
#include <algorithm>
#include <iostream>

namespace ariel {

    Board::Board() {}

    void Board::makeBoard() {
        // Initialize development cards
        initializeDevelopmentCardDeck();
        shuffleDevelopmentCardDeck();

        // Initialize tiles
        Resources resources;
        std::vector<std::string> distributedResourceTypes = resources.distributeResourceTypes();
        std::vector<int> distributedResourceNumbers = resources.distributeResourceNumbers();

        // Initialize the tiles with both resource types and numbers
        tiles.push_back(Tile(0, {0, 1, 2, 3, 4, 5}, Resources::stringToResourceType(distributedResourceTypes[0]), distributedResourceNumbers[0]));
        tiles.push_back(Tile(1, {6, 5, 4, 9, 8, 7}, Resources::stringToResourceType(distributedResourceTypes[1]), distributedResourceNumbers[1]));
        tiles.push_back(Tile(2, {10, 7, 8, 13, 12, 11}, Resources::stringToResourceType(distributedResourceTypes[2]), distributedResourceNumbers[2]));
        tiles.push_back(Tile(3, {12, 13, 14, 15, 16, 17}, Resources::stringToResourceType(distributedResourceTypes[3]), distributedResourceNumbers[3]));
        tiles.push_back(Tile(4, {8, 9, 19, 18, 14, 13}, Resources::stringToResourceType(distributedResourceTypes[4]), distributedResourceNumbers[4]));
        tiles.push_back(Tile(5, {4, 3, 21, 20, 19, 9}, Resources::stringToResourceType(distributedResourceTypes[5]), distributedResourceNumbers[5]));
        tiles.push_back(Tile(6, {2, 24, 23, 22, 21, 3}, Resources::stringToResourceType(distributedResourceTypes[6]), distributedResourceNumbers[6]));        
        tiles.push_back(Tile(7, {23, 25, 26, 27, 28, 22}, Resources::stringToResourceType(distributedResourceTypes[7]), distributedResourceNumbers[7]));
        tiles.push_back(Tile(8, {21, 22, 28, 29, 30, 20}, Resources::stringToResourceType(distributedResourceTypes[8]), distributedResourceNumbers[8]));
        tiles.push_back(Tile(9, {19, 20, 30, 31, 32, 18}, Resources::stringToResourceType(distributedResourceTypes[9]), distributedResourceNumbers[9]));  
        tiles.push_back(Tile(10, {14, 18, 32, 33, 34, 15}, Resources::stringToResourceType(distributedResourceTypes[10]), distributedResourceNumbers[10]));
        tiles.push_back(Tile(11, {16, 15, 34, 35, 36, 37}, Resources::stringToResourceType(distributedResourceTypes[11]), distributedResourceNumbers[11]));
        tiles.push_back(Tile(12, {34, 33, 40, 39, 38, 35}, Resources::stringToResourceType(distributedResourceTypes[12]), distributedResourceNumbers[12]));  
        tiles.push_back(Tile(13, {32, 31, 42, 41, 40, 33}, Resources::stringToResourceType(distributedResourceTypes[13]), distributedResourceNumbers[13]));
        tiles.push_back(Tile(14, {30, 29, 44, 43, 42, 31}, Resources::stringToResourceType(distributedResourceTypes[14]), distributedResourceNumbers[14]));
        tiles.push_back(Tile(15, {28, 27, 46, 45, 44, 29}, Resources::stringToResourceType(distributedResourceTypes[15]), distributedResourceNumbers[15]));  
        tiles.push_back(Tile(16, {44, 45, 47, 48, 49, 43}, Resources::stringToResourceType(distributedResourceTypes[16]), distributedResourceNumbers[16]));
        tiles.push_back(Tile(17, {42, 43, 49, 50, 51, 41}, Resources::stringToResourceType(distributedResourceTypes[17]), distributedResourceNumbers[17]));
        tiles.push_back(Tile(18, {40, 41, 51, 52, 53, 39}, Resources::stringToResourceType(distributedResourceTypes[18]), distributedResourceNumbers[18]));

        // After initializing tiles
        int desertIndex = -1, zeroIndex = -1;

        // Find desert and tile with number 0
        for (size_t i = 0; i < tiles.size(); ++i) {
            if (tiles[i].getType() == Resources::ResourceType::DESERT) {
                desertIndex = i;
            }
            if (tiles[i].getdiceNumber() == 0) {
                zeroIndex = i;
            }
        }

        // Ensure both desert and zero tile are found
        if (desertIndex != -1 && zeroIndex != -1) {
            // Swap their properties
            int tempNum = tiles[desertIndex].getdiceNumber();
            tiles[desertIndex].setdiceNumber(tiles[zeroIndex].getdiceNumber());
            tiles[zeroIndex].setdiceNumber(tempNum);
        }

        // Determine the maximum vertex index
        int maxVertexIndex = 0;
        for (const Tile& tile : tiles) {
            for (int vertex : tile.getVertices()) {
                if (vertex > maxVertexIndex) {
                    maxVertexIndex = vertex;
                }
            }
        }

        // Resize vertextoTiles to accommodate the maximum vertex index
        vertextoTiles.resize(maxVertexIndex + 1);

        // Map vertices to tiles
        for (const Tile& tile : tiles) {
            for (int vertex : tile.getVertices()) {
                vertextoTiles[vertex].push_back(tile.getId());
            }
        }
    }

    void Board::placeSettlement(const std::string& playerId, int vertice) {
        settlements.push_back(Settlement(playerId, vertextoTiles, vertice));
        printTilesAroundSettlement(settlements.back());
    }
    

    bool Board::isSettlementAvailable(const std::string& playerName, int vertice) const {
        // Check if vertice is valid
        if (vertice > 53 || vertice < 0) {
            std::cout << "Settlement placement failed: invalid vertice " << vertice << "." << std::endl;
            return false;
        }

        // Check if this is the first or second settlement of the player
        int playerSettlements = 0;
        for (const Settlement& settlement : settlements) {
            if (playerName == settlement.getPlayerId()) {
                playerSettlements++;
            }
        }

        // Find all tiles connected to the given vertice
        std::vector<int> vertexTiles = vertextoTiles[vertice];

        if (playerSettlements < 2) {
            // Check adjacent vertices for other players' settlements
        // Check all the edges around the vertice for adjacent settlements
        bool settlementFound = false;
        for (const int& tileIndex : vertexTiles) {
            const std::vector<std::pair<int, int>>& edges = tiles[tileIndex].getEdges();

            for (const std::pair<int, int>& edge : edges) {
                if(vertice == edge.first || vertice == edge.second){
                    int adjacentVertice = (edge.first == vertice) ? edge.second : edge.first;

                    // Check if there's a settlement on adjacent vertice
                    for (const Settlement& settlement : settlements) {
                        if (settlement.getVerticeId() == adjacentVertice) {
                            settlementFound = true;
                            break;
                        }
                    }

                    // If settlement found on adjacent vertice, print error and return false
                    if (settlementFound) {
                        std::cout << "Settlement placement failed: adjacent vertice " << adjacentVertice << " has an existing settlement." << std::endl;
                        return false;
                    }
                }
            }
        }

            // Allow placement as it's the first or second settlement
            return true;
        }

        // Beyond first two settlements: apply standard placement rules

        // Rule 1: Check all the edges around the vertice for adjacent settlements

        // Check all the edges around the vertice for adjacent settlements
        bool settlementFound = false;
        for (const int& tileIndex : vertexTiles) {
            const std::vector<std::pair<int, int>>& edges = tiles[tileIndex].getEdges();

            for (const std::pair<int, int>& edge : edges) {
                if(vertice == edge.first || vertice == edge.second){
                    int adjacentVertice = (edge.first == vertice) ? edge.second : edge.first;

                    // Check if there's a settlement on adjacent vertice
                    for (const Settlement& settlement : settlements) {
                        if (settlement.getVerticeId() == adjacentVertice) {
                            settlementFound = true;
                            break;
                        }
                    }

                    // If settlement found on adjacent vertice, print error and return false
                    if (settlementFound) {
                        std::cout << "Settlement placement failed: adjacent vertice " << adjacentVertice << " has an existing settlement." << std::endl;
                        return false;
                    }
                }
            }
        }

        // Rule 2: Ensure there is no existing settlement at the vertice
        for (const Settlement& settlement : settlements) {
            if (settlement.getVerticeId() == vertice) {
                std::cout << "Settlement placement failed: there is already a settlement at vertice " << vertice << "." << std::endl;
                return false;
            }
        }

        // Rule 3: Check if the player has a connected road that is at least 2 roads long
        for (const Road& road1 : roads) {
            if (road1.getPlayerId() == playerName && (road1.getVertices().first == vertice || road1.getVertices().second == vertice)) {
                int intermediateVertice = (road1.getVertices().first == vertice) ? road1.getVertices().second : road1.getVertices().first;
                for (const Road& road2 : roads) {
                    if (road2.getPlayerId() == playerName && (road2.getVertices().first == intermediateVertice || road2.getVertices().second == intermediateVertice)) {
                        int potentialVertice = (road2.getVertices().first == intermediateVertice) ? road2.getVertices().second : road2.getVertices().first;
                        if (potentialVertice != vertice) {
                            std::cout << "Settlement placement is allowed: player has a connected road at intermediate vertice " << intermediateVertice << "." << std::endl;
                            return true;
                        }
                    }
                }
            }
        }

        std::cout << "Settlement placement failed: no valid road connection for player " << playerName << " at vertice " << vertice << "." << std::endl;
        return false;

    }

    void Board::placeRoad(const std::string& playerId, int fromVertice, int toVertice) {
        std::pair<int,int> vertices = {fromVertice,toVertice};
        roads.push_back(Road(playerId, vertices));
    }

bool Board::isRoadAvailable(const std::string& playerName, int fromVertice, int toVertice) {

    if(fromVertice > 53 || toVertice > 53 || fromVertice < 0 || toVertice < 0){
        std::cout << "not valid vertice";
        return false;
    }
    
    std::pair<int, int> inputRoad = {fromVertice, toVertice};
    std::pair<int, int> reverseRoad = {toVertice, fromVertice};

    // Check if the road segment is already owned by another player
    for (const Road& road : roads) {
        if (road.getVertices() == inputRoad || road.getVertices() == reverseRoad) {
            if (road.getPlayerId() != playerName) {
                std::cout << "Road placement failed: the road segment is already owned by another player." << std::endl;
                return false;
            } else {
                // The player already owns this road segment
                std::cout << "Road placement failed: you already own this road segment." << std::endl;
                return false;
            }
        }
    }

    // Check how many roads the player has
    int playerRoads = 0;
    for (const Road& road : roads) {
        if (playerName == road.getPlayerId()) {
            playerRoads++;
        }
    }

    // Rule: The "fromVertice" must be connected to a settlement owned by the player
    bool hasSettlementAtFromVertice = false;
    for (const Settlement& settlement : settlements) {
        if (settlement.getVerticeId() == fromVertice && settlement.getPlayerId() == playerName) {
            hasSettlementAtFromVertice = true;
            break;
        }
    }

    // Check if the fromVertice is the toVertice of a previous road of the player
    bool isConnectedToPreviousRoad = false;
    for (const Road& road : roads) {
        if (road.getPlayerId() == playerName && road.getVertices().second == fromVertice) {
            isConnectedToPreviousRoad = true;
            break;
        }
    }

    if (!hasSettlementAtFromVertice && !isConnectedToPreviousRoad) {
        std::cout << "Road placement failed: the 'fromVertice' " << fromVertice << " must be connected to a settlement or be the 'toVertice' of a previous road owned by the player." << std::endl;
        return false;
    }

    // Beyond the first two roads: apply standard placement rules

    // Rule 1: Check if the player has a settlement at the fromVertice or it's connected to a previous road
    if (!hasSettlementAtFromVertice && !isConnectedToPreviousRoad) {
        std::cout << "Road placement failed: the player does not have a settlement at " << fromVertice << " and no connected roads to " << fromVertice << "." << std::endl;
        return false;
    }

    // Rule 3: Ensure the new road connects to a valid edge tile
    bool validEdgeTile = false;
    for (int tileId : vertextoTiles[toVertice]) {
        for (const std::pair<int, int>& edge : tiles[tileId].getEdges()) {
            if (edge == inputRoad || edge == reverseRoad) {
                validEdgeTile = true;
                break;
            }
        }
        if (validEdgeTile) {
            break;
        }
    }

    if (!validEdgeTile) {
        std::cout << "Road placement failed: the toVertice " << toVertice << " does not connect to a valid edge tile." << std::endl;
        return false;
    }

    std::cout << "Road placement is allowed for player " << playerName << " from vertice " << fromVertice << " to vertice " << toVertice << "." << std::endl;
    return true;
}



    void Board::initializeDevelopmentCardDeck() {
        developmentCardDeck = DevelopmentCard::initializeDeck();
    }

    void Board::shuffleDevelopmentCardDeck() {
        DevelopmentCard::shuffleDeck(developmentCardDeck);
    }

    DevelopmentCard Board::drawDevelopmentCard() {
        return DevelopmentCard::drawCard(developmentCardDeck);
    }

    std::vector<Settlement>& Board::getSettlements() {
        return settlements;
    }

    std::vector<Road>& Board::getRoads() {
        return roads;
    }

    std::vector<std::vector<int>>& Board::getVertexToTiles() {
        return vertextoTiles;
    }

    Tile& Board::getTileAtIndex(int tileId) {
        return tiles[tileId];
    }

    int Board::getNumSettlements(const std::string& player) {
        int numSettlements = 0;
        for (const Settlement& settlement : settlements) {
            if (settlement.getPlayerId() == player) {
                numSettlements++;
            }
        }
        return numSettlements;
    }

    int Board::getNumRoads(const std::string& player) {
        int numRoads = 0;
        for (const Road& road : roads) {
            if (road.getPlayerId() == player) {
                numRoads++;
            }
        }
        return numRoads;
    }

    void Board::printAllTiles() const {
        // Iterate over each settlement
        for (const Settlement& settlement : settlements) {
            int vertexId = settlement.getVerticeId();

            // Find all tile IDs around the settlement's vertex
            std::vector<int> tileIds;
            for (const Tile& tile : tiles) {
                bool found = false;
                for (int tileVertex : tile.getVertices()) {
                    if (tileVertex == vertexId) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    tileIds.push_back(tile.getId());
                }
            }
            // Print settlements for each tile found
            for (int tileId : tileIds) {
                std::cout << "Tile ID: " << tileId
                          << ", Resource Type: " << Resources::resourceTypeToString(tiles[tileId].getType())
                          << ", Settlements: " << settlement.getPlayerId() << std::endl;
            }
        }
    }

    void Board::printTilesAroundSettlement(const Settlement& settlement) const {
        std::cout << "Settlement placed by player " << settlement.getPlayerId() << " at vertex " << settlement.getVerticeId() << " is adjacent to tiles:" << std::endl;
        for (int tileId : vertextoTiles[settlement.getVerticeId()]) {
            std::cout << "Tile ID: " << tileId
                      << ", Resource Type: " << Resources::resourceTypeToString(tiles[tileId].getType())
                      << std::endl;
        }
    }

    void Board::printAllTilesInfo() const {
        std::cout << "Tiles Information:" << std::endl;
        for (const Tile& tile : tiles) {
            std::cout << "Tile ID: " << tile.getId()
                    << ", Resource Type: " << Resources::resourceTypeToString(tile.getType())
                    << ", Dice Roll: " << tile.getdiceNumber()
                    << std::endl;
        }
    }

    std::vector<int> Board::getTilesAroundSettlement(const Settlement& settlement) const {
        return vertextoTiles[settlement.getVerticeId()];
    }

    void Board::addPlayer(Player& player) {
        players.push_back(Player(player));
    }

    // Return a reference to the players vector
    std::vector<Player>& Board::getPlayers() {
        return players;
    }
    
    // Update player by reference
    void Board::updatePlayer(Player& updatedPlayer) {
        for (Player& player : players) {
            if (player.getName() == updatedPlayer.getName()) {
                player = updatedPlayer;
                break;
            }
        }
    }
    void Board::resetGame() {
        // Clear settlements, roads, tiles, players, and any other relevant data structures
        settlements.clear();
        roads.clear();
        tiles.clear();
        players.clear();
        vertextoTiles.clear();
        developmentCardDeck.clear();

        // Reset the turn counter
        std::cout << "game has been cleared" << std::endl;
    }

} // namespace ariel
