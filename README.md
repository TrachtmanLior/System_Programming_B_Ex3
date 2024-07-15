# Catan Game Implementation

Author: Lior Trachtman  
Email: lior16122000@gmail.com

## Overview

This project implements a simplified version of the popular board game Catan. The game is designed to be played by multiple players, each competing to build settlements, cities, and roads, gather resources, and earn victory points.

## Rules of the Game

### Objective
The objective of the game is to be the first player to reach a specified number of victory points, typically 10 points in the standard Catan game.

### Game Setup
1. **Board Setup**: The game board consists of 19 hexagonal tiles arranged in a random layout, each representing different terrain types such as forest (wood), hills (brick), pasture (wool), fields (grain), mountains (ore), and a desert (no resources). Each tile has a corresponding number token that determines when resources are produced.
   
2. **Initial Placement**: Players take turns placing 2 settlements and 2 roads on the board. Settlements must be placed at intersections where three tiles meet, and roads connect these settlements. Each player earns initial resources based on the adjacent terrain types of their settlements.

3. **Resources**: Resources are vital for gameplay and are collected from settlements and cities based on dice rolls. When a player's number token is rolled, they receive resources for each adjacent settlement or city.

### Gameplay
1. **Turn Phases**:
   - **Roll Dice**: At the beginning of each player's turn, two six-sided dice are rolled. The combined number determines which terrain hexes produce resources.
   
   - **Resource Collection**: Players collect resources based on their settlements and cities adjacent to the rolled number. Cities generate double the resources compared to settlements.
   
   - **Trading and Building**: After collecting resources, players can trade with each other or with the bank to obtain necessary resources for building roads, settlements, or cities. Trading can involve exchanging resource cards at mutually agreed rates.
   
   - **Development Cards**: Players can use resources to purchase development cards from the deck. These cards provide various advantages such as gaining resources, building roads without resources, or earning victory points.
   
   - **Largest Army**: Special bonuses are awarded to the player with the longest continuous road and the player who plays the most Knight cards, respectively.

2. **Development Cards**:
   - **Types**:
     - **Progress Cards**: Include Monopoly (forces other players to give up all resources of a chosen type), Road Building (build two roads for free), and Year of Plenty (choose two resources from the bank).
     - **Knight Cards**: Collect three Knight cards to earn the Largest Army card, worth 2 victory points.
     - **Victory Point Cards**: Directly award 1 victory point each.

3. **Building**:
   - **Roads**: Cost 1 brick and 1 wood. Roads extend from settlements or other roads and must form a continuous path.
   - **Settlements**: Cost 1 brick, 1 wood, 1 wool, and 1 grain. Must be placed at least two road lengths apart from other settlements.
   - **Cities**: Upgrade a settlement by paying 3 ore and 2 grain. Cities generate double resources and are worth 2 victory points.

### Victory Conditions
The game ends immediately when a player reaches or exceeds 10 victory points at the end of their turn.

### Additional Notes
- **Trading**: Players can negotiate trades freely, including resource cards or promises of future favors.
- **Game Variants**: Variants can include adjustments to the victory point goal, custom rules for trading, or additional development card types.

## Class Hierarchy

### Board Class (`board.hpp`)

The `Board` class represents the game board in the Catan game implementation. It manages players, settlements, roads, tiles, development cards, and game state.

#### Attributes
- `players`: Vector of `Player` objects representing all players in the game.
- `settlements`: Vector of `Settlement` objects representing settlements on the board.
- `roads`: Vector of `Road` objects representing roads on the board.
- `tiles`: Vector of `Tile` objects representing hexagonal tiles on the board.
- `vertextoTiles`: 2D vector mapping vertices to tiles on the board.
- `developmentCardDeck`: Vector of `DevelopmentCard` objects representing the deck of development cards.
- `developmentCardDiscardPile`: Vector of `DevelopmentCard` objects representing the discard pile for development cards.

#### Methods
- `makeBoard()`: Initializes the board with tiles and vertices.
- `placeSettlement(const std::string& playerId, int vertice)`: Places a settlement on a vertex for a player.
- `isSettlementAvailable(const std::string& playerName, int vertice) const`: Checks if a settlement can be placed on a vertex.
- `placeRoad(const std::string& playerId, int fromVertice, int toVertice)`: Places a road between two vertices for a player.
- `initializeDevelopmentCardDeck()`: Initializes the deck of development cards.
- `shuffleDevelopmentCardDeck()`: Shuffles the development card deck.
- `drawDevelopmentCard()`: Draws a development card from the deck.
- `getSettlements()`, `getRoads()`, `getVertexToTiles()`: Getter methods for settlements, roads, and vertex-to-tiles mapping.
- `getTileAtIndex(int tileId)`: Retrieves a specific tile by its index.
- `getNumSettlements(const std::string& player)`, `getNumRoads(const std::string& player)`: Returns the number of settlements and roads owned by a player.
- `printAllTiles()`, `printTilesAroundSettlement(const Settlement& settlement)`, `printAllTilesInfo()`: Methods for printing tile information.
- `getTilesAroundSettlement(const Settlement& settlement)`: Returns vertices adjacent to a settlement.
- `updatePlayer(Player& updatedPlayer)`, `addPlayer(Player& player)`: Methods to update and add players.
- `resetGame()`: Resets the game state.

### Catan Class (`catan.hpp`)

The `Catan` class manages the overall game flow, including turns, player actions, and game status.

#### Attributes
- `board`: Instance of `Board` class representing the game board.
- `currentPlayerIndex`: Index of the current player.
- `currentTurn`: Current turn number.
- `finishedPlayersCount`: Number of players who have finished their turns.
- `gameStarted`: Flag indicating if the game has started.
- `gameEnded`: Flag indicating if the game has ended.

#### Methods
- `Catan()`: Constructor to initialize the game.
- `run()`: Function to start running the game.
- `setupGame()`: Function to set up the game before it starts.
- `playTurn()`: Function to play a single turn.
- `handleTurn(Player& player)`: Function to handle a player's turn.
- `printGameStatus()`: Function to print the current game status.
- `checkGameEnd()`: Function to check if the game has ended.
- `handleTrade(Player& currentPlayer)`: Function to handle trading between players.
- `getCurrentTurn()`, `getCurrentPlayerIndex()`: Getter methods for current turn and current player index.
- `getBoard()`: Getter method for the game board.
- `isGameStarted()`: Function to check if the game has started.

### DevelopmentCard Class (`developmentCard.hpp`)

The `DevelopmentCard` class represents development cards used in the Catan game, including types like Knight, Victory Point, Road Building, Monopoly, and Year of Plenty.

#### Attributes
- `type`: `DevelopmentCardType` enum representing the type of the development card.
- `description`: Description of the development card.

#### Methods
- `DevelopmentCard(DevelopmentCardType type)`: Constructor with type parameter.
- `getType()`, `getDescription()`: Getter methods for type and description.
- `printCardDetails()`: Method to print details of the development card.
- `static initializeDeck()`: Static method to initialize a deck of development cards.
- `static shuffleDeck(std::vector<DevelopmentCard>& deck)`: Static method to shuffle a deck of development cards.
- `static drawCard(std::vector<DevelopmentCard>& deck)`: Static method to draw a card from a deck.
- `static stringToDevelopmentCardType(const std::string& cardString)`: Static method to convert a string to `DevelopmentCardType` enum.
- `static isValidDevelopmentCardType(const std::string& card)`: Static method to check if a string is a valid `DevelopmentCardType`.
- `developmentCardTypeToString(DevelopmentCardType type)`: Method to convert `DevelopmentCardType` enum to string.

### Player Class (`player.hpp`)

The `Player` class represents a player in the Catan game, managing player-specific attributes like points, resources, cards, and game actions.

#### Attributes
- `playerId`: Unique identifier for the player.
- `points`: Player's total points.
- `knights`: Number of knight cards owned by the player.
- `turnsPlayed`: Number of turns this player has played.
- `roadBuildingCardActivated`: Flag indicating if the road building card is activated.
- `hasLargestArmy`: Flag indicating if the player has the largest army.
- `players`, `roads`, `developmentCards`, `resources`: Vectors storing players, roads, development cards, and resources owned by the player.
- `static currentPlayer`, `playerWithLargestArmy`: Pointers tracking current player and player with largest army.

#### Methods
- Constructor (`Player(const std::string& playerId)`): Initializes a player with a given playerId.
- Methods for managing settlements, roads, dice rolls, trading, resources, development cards, turns played, and game statistics.
- `checkLargestArmy(Board& board)`: Method to check if the player has achieved the largest army status.

### Resources Class (`resources.hpp`)

The `Resources` class defines resource types and provides methods for managing resources in the Catan game.

#### Attributes
- `resourceTypes`: Vector holding resource type names.
- `resourceNumbers`: Vector holding resource numbers.

#### Methods
- Constructor (`Resources()`): Initializes resource type names and numbers.
- `static resourceTypeToString(ResourceType resourceType)`: Converts `ResourceType` enum to string.
- `static stringToResourceType(const std::string& resourceString)`: Converts string to `ResourceType` enum.
- `distributeResourceTypes()`, `distributeResourceNumbers()`: Methods to distribute resource types and numbers.

### Road Class (`road.hpp`)

The `Road` class represents roads placed on the Catan game board between vertices.

#### Attributes
- `vertices`: Pair of vertices representing the starting and ending points of the road.
- `playerId`: Player who owns the road.

#### Methods
- Constructor (`Road(const std::string& playerId, const std::pair<int, int>& vertices)`): Initializes playerId and vertices.
- Getter methods for retrieving vertices and playerId.

### Settlement Class (`settlement.hpp`)

The `Settlement` class represents settlements and cities placed on vertices of the Catan game board.

#### Attributes
- `playerId`: Player ID who owns the settlement.
- `vertextoTiles`: Reference to a 2D vector representing tiles on the board.
- `verticeId`: ID of the vertex where the settlement is placed.
- `cityStatus`: Flag indicating if the settlement has been upgraded to a city.

#### Methods
- Constructor (`Settlement(std::string playerId, std::vector<std::vector<int>>& vertextoTiles, int verticeId)`): Initializes playerId, vertextoTiles, and verticeId.
- Methods for placing settlements, upgrading to cities, and checking settlement status.

### Tile Class (`tile.hpp`)

The `Tile` class represents hexagonal tiles on the Catan game board, each providing resources and having associated vertices and edges.

#### Attributes
- `id`: Unique identifier for the tile.
- `vertices`: Vertices associated with the tile.
- `type`: `ResourceType` enum representing the type of resource provided by the tile.
- `edges`: Pairs of vertex indices representing edges connecting vertices.
- `diceNumber`: Number on the dice that activates this tile.

#### Methods
- Constructor (`Tile(int id, std::vector<int> vertices, Resources::ResourceType type, int diceNumber)`): Initializes tile attributes.
- Getter and setter methods for retrieving and modifying tile attributes.

    // Determine winner and end game
    std::cout << "Game Over! Winner: " << (player1.getPoints() >= 10 ? "Player1" : "Player2") << std::endl;

    return 0;

}
### Board Structure
![IMG_48FC685221FB-1](https://github.com/user-attachments/assets/05f69bb8-cb05-4c2f-8932-404cdc25843e)


## Usage
1. Clone the repository.

- `make catan` - compiles the project, creating exec file `catan` to run the game.
- `./catan` - runs the game.

### Tests

Tests:
- `make test` -     run using `./test`  (advanced doctest)
- `make tidy` -     makes sure the code is clean
- `make valgrind` - makes sure there are no memory leaks/problems.


#### clang-tidy and valgrind
Before submitting we ran clang-tidy to make sure the code is written well, and valgrind to make sure there are no memory errors or leaks.

#### Test.cpp
This file includes tests on everything implemented in the Tree class. It tests the methods, the iterators, and the operators.
