// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#include "doctest.h"
#include "Board.hpp"
#include "Player.hpp"
#include "Settlement.hpp"
#include "Road.hpp"
#include "DevelopmentCard.hpp"
#include "Resources.hpp"
#include "Tile.hpp"
#include "Catan.hpp"

using namespace ariel;

TEST_CASE("Player functions") {
    // Create a board and initialize it
    Board board;
    board.makeBoard();

    // Create players and add them to the board
    Player player("Player1");
    board.addPlayer(player);

    // Test setting and getting points
    player.setPoints(5);
    CHECK(player.getPoints() == 5);

    // Test adding and removing resources
    player.addResource(Resources::ResourceType::WOOD, 3, board);
    CHECK(player.getResourceCount(Resources::ResourceType::WOOD) == 3);

    player.removeResource(Resources::ResourceType::WOOD, 1, board);
    CHECK(player.getResourceCount(Resources::ResourceType::WOOD) == 2);

    // Test placing settlement and road
    player.placeSettlement(0, board);
    CHECK(board.getNumSettlements("Player1") == 1);

    player.placeRoad(0, 1, board);
    CHECK(board.getNumRoads("Player1") == 1);
}

TEST_CASE("Board initialization and basic functions") {
    Board board;
    board.makeBoard();
    
    CHECK(board.getPlayers().empty());
    CHECK(board.getSettlements().empty());
    CHECK(board.getRoads().empty());
    CHECK(board.getVertexToTiles().size() == 54);
    CHECK(board.getTileAtIndex(0).getId() == 0);

    Player player1("Player1");
    Player player2("Player2");
    
    board.addPlayer(player1);
    board.addPlayer(player2);
    
    CHECK(board.getPlayers().size() == 2);
    CHECK(board.getPlayers()[0].getName() == "Player1");
    CHECK(board.getPlayers()[1].getName() == "Player2");

    board.resetGame();
    CHECK(board.getPlayers().empty());
}


TEST_CASE("Board settlement and road placement") {
    Board board;
    board.makeBoard();

    Player player1("Player1");
    Player player2("Player2");
    board.addPlayer(player1);
    board.addPlayer(player2);

    // Place settlements and roads for both players
    player1.placeSettlement(0, board);
    player1.placeRoad(0, 1, board);

    player2.placeSettlement(3, board);
    player2.placeRoad(3, 4, board);

    // Check number of settlements and roads for each player
    CHECK(board.getNumSettlements("Player1") == 1);
    CHECK(board.getNumSettlements("Player2") == 1);

    CHECK(board.getNumRoads("Player1") == 1);
    CHECK(board.getNumRoads("Player2") == 1);
}

TEST_CASE("Board dice roll and resource collection") {
    Board board;
    board.makeBoard();

    Player player1("Player1");
    Player player2("Player2");
    board.addPlayer(player1);
    board.addPlayer(player2);

    // Roll dice and distribute resources accordingly
    player1.rollDice(board);

    // Check if resources are correctly distributed to the player
    CHECK(player1.getResourceCount(Resources::ResourceType::WOOD) >= 0);
    CHECK(player1.getResourceCount(Resources::ResourceType::BRICK) >= 0);
    CHECK(player1.getResourceCount(Resources::ResourceType::ORE) >= 0);
    CHECK(player1.getResourceCount(Resources::ResourceType::GRAIN) >= 0);
    CHECK(player1.getResourceCount(Resources::ResourceType::WOOL) >= 0);
}

TEST_CASE("Player development card purchase and usage") {
    Board board;
    board.makeBoard();

    Player player1("Player1");
    board.addPlayer(player1);

    // Add resources to player for purchasing development cards
    player1.addResource(Resources::ResourceType::ORE, 1, board);
    player1.addResource(Resources::ResourceType::WOOL, 1, board);
    player1.addResource(Resources::ResourceType::GRAIN, 1, board);

    // Purchase a development card and verify if it's added to player's hand
    player1.buyDevelopmentCard(board);
    CHECK(player1.hasDevelopmentCard());

    // Play the development card (e.g., Knight card)
    player1.playDevelopmentCard(DevelopmentCardType::KNIGHT, board);

    // Verify the effect of the development card on the game state
    // Example: Check if the robber position changes or another player's resource is affected
}

TEST_CASE("Board reset and state after game completion") {
    Board board;
    board.makeBoard();

    Player player1("Player1");
    Player player2("Player2");
    board.addPlayer(player1);
    board.addPlayer(player2);

    // Play through a full game or until completion
    // Example: Players build settlements, roads, cities, purchase development cards, etc.

    // Reset the game board and verify initial state for a new game
    board.resetGame();
    CHECK(board.getPlayers().empty());
    CHECK(board.getSettlements().empty());
    CHECK(board.getRoads().empty());
}

TEST_CASE("Player victory point calculation from settlements and cities") {
    Board board;
    board.makeBoard();

    Player player1("Player1");
    board.addPlayer(player1);

    // Add resources to player
    player1.addResource(Resources::ResourceType::ORE, 3, board);
    player1.addResource(Resources::ResourceType::WOOL, 1, board);
    player1.addResource(Resources::ResourceType::BRICK, 1, board);
    player1.addResource(Resources::ResourceType::WOOD, 1, board);
    player1.addResource(Resources::ResourceType::GRAIN, 3, board);

    // Build settlements and cities to earn victory points
    player1.placeSettlement(0, board);
    player1.placeCity(0,board);

    // Check the total victory points of the player
    CHECK(player1.getPoints() >= 2); // Assuming 2 points from settlement and city
}

TEST_CASE("DevelopmentCard functions") {
    DevelopmentCard knightCard(DevelopmentCardType::KNIGHT);
    CHECK(knightCard.getType() == DevelopmentCardType::KNIGHT);
    CHECK(knightCard.getDescription() == "Knight card - lets the player move the robber");

    auto deck = DevelopmentCard::initializeDeck();
    CHECK(deck.size() == 25);

    DevelopmentCard::shuffleDeck(deck);
    auto discardPile = std::vector<DevelopmentCard>();
    auto drawnCard = DevelopmentCard::drawCard(deck);
    CHECK(!deck.empty());
}

TEST_CASE("Player functions") {
    Player player("Player1");
    Board board;
    board.makeBoard();

    player.setPoints(5);
    CHECK(player.getPoints() == 5);

    player.addResource(Resources::ResourceType::WOOD, 3, board);
    CHECK(player.getResourceCount(Resources::ResourceType::WOOD) == 3);

    player.removeResource(Resources::ResourceType::WOOD, 1, board);
    CHECK(player.getResourceCount(Resources::ResourceType::WOOD) == 2);

    player.placeSettlement(0, board);
    CHECK(board.getNumSettlements("Player1") == 1);

    player.placeRoad(0, 1, board);
    CHECK(board.getNumRoads("Player1") == 1);
}

TEST_CASE("Resource distribution functions") {
    auto resources = Resources();
    auto resourceTypes = resources.distributeResourceTypes();
    auto resourceNumbers = resources.distributeResourceNumbers();

    CHECK(resourceTypes.size() == 19);
    CHECK(resourceNumbers.size() == 19);

    CHECK(Resources::resourceTypeToString(Resources::ResourceType::WOOD) == "Wood");
    CHECK(Resources::stringToResourceType("Brick") == Resources::ResourceType::BRICK);
}

TEST_CASE("Road functions") {
    Road road("Player1", {0, 1});
    CHECK(road.getVertices().first == 0);
    CHECK(road.getVertices().second == 1);
    CHECK(road.getPlayerId() == "Player1");
}

TEST_CASE("Settlement functions") {
    std::vector<std::vector<int>> vertexToTiles;
    Settlement settlement("Player1", vertexToTiles, 0);

    CHECK(settlement.getPlayerId() == "Player1");
    CHECK(settlement.getVerticeId() == 0);
    CHECK(!settlement.isCity());

    settlement.upgradeToCity();
    CHECK(settlement.isCity());
}

TEST_CASE("Tile functions") {
    std::vector<int> vertices = {0, 1, 2, 3, 4, 5};
    Tile tile(1, vertices, Resources::ResourceType::WOOD, 6);

    CHECK(tile.getId() == 1);
    CHECK(tile.getVertices() == vertices);
    CHECK(tile.getType() == Resources::ResourceType::WOOD);
    CHECK(tile.getdiceNumber() == 6);

    std::vector<std::pair<int, int>> edges = tile.getEdges();
    CHECK(edges.size() == 6);
}

TEST_CASE("Full game flow") {
    Board board;
    Player player1("Player1");
    Player player2("Player2");

    board.addPlayer(player1);
    board.addPlayer(player2);

    board.makeBoard();
    board.initializeDevelopmentCardDeck();
    board.shuffleDevelopmentCardDeck();

    player1.addResource(Resources::ResourceType::WOOD, 2, board);
    player1.addResource(Resources::ResourceType::BRICK, 2, board);

    player1.placeSettlement(0, board);
    player1.placeRoad(0, 1, board);

    CHECK(board.getNumSettlements("Player1") == 1);
    CHECK(board.getNumRoads("Player1") == 1);

    auto card = board.drawDevelopmentCard();
    player1.playDevelopmentCard(card.getType(), board);

    player1.trade(player2, "Wood", "Brick", 1, 1, board);

    player2.rollDice(board);
}


TEST_CASE("Player resource trading") {
    Board board;
    board.makeBoard();
    Player player1("Player1");
    Player player2("Player2");
    board.addPlayer(player1);
    board.addPlayer(player2);

    // Initialize resources for testing
    player1.addResource(Resources::ResourceType::WOOD, 3, board);
    player1.addResource(Resources::ResourceType::BRICK, 2, board);
    player2.addResource(Resources::ResourceType::WOOD, 2, board);
    player2.addResource(Resources::ResourceType::BRICK, 3, board);

    SUBCASE("Valid trade with sufficient resources") {
        // Trade where player1 gives 2 Wood and gets 1 Brick from player2
        player1.trade(player2, "Wood", "Brick", 2, 1, board);

        // Check player1's resources after trade
        CHECK(player1.getResourceCount(Resources::ResourceType::WOOD) == 1);
        CHECK(player1.getResourceCount(Resources::ResourceType::BRICK) == 3);

        // Check player2's resources after trade
        CHECK(player2.getResourceCount(Resources::ResourceType::WOOD) == 4); // 2 (initial) + 2 (traded)
        CHECK(player2.getResourceCount(Resources::ResourceType::BRICK) == 2); // 3 (initial) - 1 (traded)
    }

    SUBCASE("Invalid trade with insufficient resources") {
        // Attempt trade where player1 gives 4 Wood (insufficient) and expects 2 Brick from player2
        player1.trade(player2, "Wood", "Brick", 4, 2, board);

        // Check player1's resources remain unchanged
        CHECK(player1.getResourceCount(Resources::ResourceType::WOOD) == 3);
        CHECK(player1.getResourceCount(Resources::ResourceType::BRICK) == 2);

        // Check player2's resources remain unchanged
        CHECK(player2.getResourceCount(Resources::ResourceType::WOOD) == 2);
        CHECK(player2.getResourceCount(Resources::ResourceType::BRICK) == 3);
    }

    SUBCASE("Trade with different amounts and types") {
        // Trade where player1 gives 1 Wood and gets 2 Brick from player2
        player1.trade(player2, "Wood", "Brick", 1, 2, board);

        // Check player1's resources after trade
        CHECK(player1.getResourceCount(Resources::ResourceType::WOOD) == 2);
        CHECK(player1.getResourceCount(Resources::ResourceType::BRICK) == 4); // 2 (initial) + 2 (traded)

        // Check player2's resources after trade
        CHECK(player2.getResourceCount(Resources::ResourceType::WOOD) == 3); // 2 (initial) - 1 (traded)
        CHECK(player2.getResourceCount(Resources::ResourceType::BRICK) == 1); // 3 (initial) + 2 (traded)
    }

    SUBCASE("Trade with invalid resource types") {
        // Attempt trade with invalid resource types
        player1.trade(player2, "InvalidResource", "Brick", 1, 1, board);

        // Check player1's and player2's resources remain unchanged
        CHECK(player1.getResourceCount(Resources::ResourceType::WOOD) == 3);
        CHECK(player1.getResourceCount(Resources::ResourceType::BRICK) == 2);
        CHECK(player2.getResourceCount(Resources::ResourceType::WOOD) == 2);
        CHECK(player2.getResourceCount(Resources::ResourceType::BRICK) == 3);
    }
}


TEST_CASE("Player acquires development cards and checks resource availability") {
    Board board;
    board.makeBoard();
    Player player1("Player1");
    Player player2("Player2");
    board.addPlayer(player1);
    board.addPlayer(player2);

    // Add sufficient resources for testing
    player1.addResource(Resources::ResourceType::WOOD, 100, board);
    player1.addResource(Resources::ResourceType::BRICK, 100, board);
    player1.addResource(Resources::ResourceType::ORE, 100, board);
    player1.addResource(Resources::ResourceType::GRAIN, 100, board);
    player1.addResource(Resources::ResourceType::WOOL, 100, board);

    player1.buyDevelopmentCard(board);

    // Assertions to verify player's state after buying development cards
    CHECK(player1.hasDevelopmentCard());
    CHECK(player1.hasResourcesForCityBuilding());
    CHECK(player1.hasResourcesForDevelopmentCard());
    CHECK(player1.hasResourcesForRoadBuilding());
    CHECK(player1.hasResourcesForSettlementBuilding());
}




TEST_CASE("Tile edge functionality") {
    // Create a tile with known edges
    Tile tile(0, {0, 1, 2, 3, 4, 5}, Resources::ResourceType::WOOD, 6);

    // Retrieve edges and verify their correctness
    auto edges = tile.getEdges();

    // Check number of edges
    CHECK(edges.size() == 6);

    // Verify each edge
    CHECK(edges[0] == std::make_pair(0, 1));
    CHECK(edges[1] == std::make_pair(1, 2));
    CHECK(edges[2] == std::make_pair(2, 3));
    CHECK(edges[3] == std::make_pair(3, 4));
    CHECK(edges[4] == std::make_pair(4, 5));
    CHECK(edges[5] == std::make_pair(5, 0));
}
