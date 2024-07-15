/**
 * written by Lior Trachtman: 211791041
 * EMAIL: lior16122000@gmail.com
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"

using namespace std;
using namespace ariel;

void runDemo() {
    //=====================INIT board and players================================
    Board board;
    board.makeBoard();
    
    std::vector<Player> players;

    // Create 4 players
    Player player1("Player1");
    Player player2("Player2");
    Player player3("Player3");
    Player player4("Player4");

    // Add players to the board
    board.addPlayer(player1);
    board.addPlayer(player2);
    board.addPlayer(player3);
    board.addPlayer(player4);

    board.printAllTilesInfo();
    std::cout << "\n\n\n";

    //====================Init settlement and road placements===================
    // Player one builds settlement on vertice 44 and road from 44 to 29
    player1.placeSettlement(44, board);
    std::cout << "\n";
    player1.placeRoad(44, 29, board);
    std::cout << "\n";

    // Player two builds settlement on vertice 32 and road from 32 to 18
    player2.placeSettlement(32, board);
    std::cout << "\n";
    player2.placeRoad(32, 18, board);
    std::cout << "\n";

    // Player three builds settlement on vertice 14 and road from 14 to 18
    player3.placeSettlement(14, board);
    std::cout << "\n";
    player3.placeRoad(14, 18, board);
    std::cout << "\n";

    // Player four builds settlement on vertice 51 and road from 51 to 52
    player4.placeSettlement(51, board);
    std::cout << "\n";
    player4.placeRoad(51, 52, board);
    std::cout << "\n";

    // Player one builds settlement on vertice 21 and road from 21 to 20
    player1.placeSettlement(21, board);
    std::cout << "\n";
    player1.placeRoad(21, 20, board);
    std::cout << "\n";

    // Player two builds settlement on vertice 34 and road from 34 to 15
    player2.placeSettlement(34, board);
    std::cout << "\n";
    player2.placeRoad(34, 15, board);
    std::cout << "\n";

    // Player three builds settlement on vertice 9 and road from 9 to 4
    player3.placeSettlement(9, board);
    std::cout << "\n";
    player3.placeRoad(9, 4, board);
    std::cout << "\n";

    // Player four builds settlement on vertice 0 and road from 0 to 5
    player4.placeSettlement(0, board);
    std::cout << "\n";
    player4.placeRoad(0, 5, board);

    std::cout << "\n\n\n\n";
    board.printAllTiles();

    std::cout << "\n";

    player1.printStats(board);

    std::cout << "\n";

    // Add resources to players
    player1.addResource(Resources::stringToResourceType("Wool"), 50, board);
    player1.addResource(Resources::stringToResourceType("Wood"), 50, board);
    player1.addResource(Resources::stringToResourceType("Brick"), 50, board);
    player1.addResource(Resources::stringToResourceType("Ore"), 50, board);
    player1.addResource(Resources::stringToResourceType("Grain"), 50, board);
    player2.addResource(Resources::stringToResourceType("Grain"), 50, board);

    for (int i = 0; i < 7; i++) {
        for (Player& player : board.getPlayers()) {
            player.rollDice(board);
            std::cout << "\n";
        }
    }

    // Add more resources to players
    player1.addResource(Resources::stringToResourceType("Wool"), 50, board);
    player1.addResource(Resources::stringToResourceType("Wood"), 50, board);
    player1.addResource(Resources::stringToResourceType("Brick"), 50, board);
    player1.addResource(Resources::stringToResourceType("Ore"), 50, board);
    player1.addResource(Resources::stringToResourceType("Grain"), 50, board);
    player2.addResource(Resources::stringToResourceType("Grain"), 50, board);

    // Player building
    player1.placeRoad(20, 30, board);
    player1.placeSettlement(30, board);
    player1.placeRoad(29, 28, board);
    player1.placeRoad(28, 27, board);
    player1.placeSettlement(27, board);
    player1.placeCity(44, board);
    player1.placeCity(21, board);
    player1.placeCity(30, board);
    player1.placeCity(27, board);

    std::cout << "\n\n\n";

    //invalid building:
    //road that is not connected to a prev road
    player1.placeRoad(44,50,board);

    //road building not from settlement
    player1.placeRoad(50, 51, board);

    //building settlement not from a connected road
    player1.placeSettlement(53,board);

    //building settlement on another player settlement vertice
    player1.placeSettlement(9,board);

    std::cout << "\n\n\n\n\n\n\n";

    player1.trade(player2, "Ore", "Grain", 1, 30, board);

    std::cout << "\n\n\n\n\n\n\n";

    std::cout << player1.getTotalResources() << "\n";
    player1.printStats(board);

    // Step 4: Player one buys and uses 15 development cards
    for (int i = 0; i < 15; ++i) {
        player1.buyDevelopmentCard(board);
    }
    player1.playDevelopmentCard(DevelopmentCard::stringToDevelopmentCardType("Knight"), board);
    player1.playDevelopmentCard(DevelopmentCard::stringToDevelopmentCardType("Knight"), board);
    player1.playDevelopmentCard(DevelopmentCard::stringToDevelopmentCardType("Knight"), board);
    std::cout << "\n";
    player1.playDevelopmentCard(DevelopmentCard::stringToDevelopmentCardType("Victory Point"), board);
    std::cout << "\n";
    player1.playDevelopmentCard(DevelopmentCard::stringToDevelopmentCardType("Year of Plenty"), board);
    std::cout << "\n";
    player1.playDevelopmentCard(DevelopmentCard::stringToDevelopmentCardType("Monopoly"), board);
    std::cout << "\n";
    player1.playDevelopmentCard(DevelopmentCard::stringToDevelopmentCardType("Road Building"), board);
    std::cout << "\n";

    std::cout << "\n\n\n\n\n\n\n";
    player1.printStats(board);
    player2.printStats(board);

    std::cout << "\n\n\n\n\n\n\n";

    player1.trade(player2, "Knight", "Grain", 5, 10, board);

    std::cout << "\n\n\n\n\n\n\n";

    player1.printStats(board);
    player2.printStats(board);

    std::cout << "\n\n\n\n\n\n\n";

    // Step 2: Player one builds more roads and settlements
    player1.placeRoad(29, 28, board);
    player1.placeRoad(28, 27, board);
    player1.placeSettlement(27, board);
    player1.placeRoad(27, 26, board);
    player1.placeSettlement(26, board);

    // Step 3: Player two upgrades settlements to cities
    player2.placeCity(32, board);
    player2.placeCity(34, board);
    player4.placeCity(0, board);

    player1.placeCity(27, board);
    player1.placeCity(26, board);

    player1.printStats(board);
    player2.printStats(board);
    player3.printStats(board);
    player4.printStats(board);

    std::cout << "\n\n\n\n ===========RESET GAME============ \n\n\n";
    board.resetGame();
}

int main() {
    int choice;

    while (true) {
        std::cout << "Choose the program to run:\n";
        std::cout << "1. Demo\n";
        std::cout << "2. Run the Catan game\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            runDemo();
            break; // Exit the loop if choice is valid
        } else if (choice == 2) {
            ariel::Catan game;
            game.run();
            break; // Exit the loop if choice is valid
        } else {
            std::cout << "Invalid choice. Please enter 1 or 2.\n";
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        }
    }

    return 0;
}