// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#include "Player.hpp"
#include <iostream>
#include <stdexcept>

namespace ariel {

    Player* Player::playerWithLargestArmy = nullptr; // Initialize static member for player with largest army

    Player::Player(const std::string& playerId) {
        // Constructor to initialize a player with given playerId
        this->playerId = playerId;
        this->points = 0;
        this->knights = 0;
        this->roadBuildingCardActivated = false;
        this->hasLargestArmy = false;
        this->roads = std::vector<Road>();
        players = std::vector<Player>();
        developmentCards = std::vector<DevelopmentCard>();

        // Initialize resources with 0 quantity for each type
        resources = {
            {Resources::ResourceType::GRAIN, 0},
            {Resources::ResourceType::WOOL, 0},
            {Resources::ResourceType::ORE, 0},
            {Resources::ResourceType::WOOD, 0},
            {Resources::ResourceType::BRICK, 0}
        };
    }

    std::vector<Player> Player::getPlayers() {
        return players; // Getter for the vector of all players in the game
    }

    void Player::setPlayers(Player& player) {
        this->players.push_back(player); // Setter to add a player to the vector of all players
    }

    void Player::rollDice(Board& board) {
        int diceRoll = rand() % 6 + 1 + rand() % 6 + 1; // Roll two six-sided dice
        std::cout << playerId << " rolled a " << diceRoll << std::endl; // Output the dice roll result

        if (diceRoll == 7) {
            // Handle the robber
            for (Player& player : board.getPlayers()) {
                if (player.getTotalResources() > 7) {
                    player.loseHalfResources(); // If player has more than 7 resources, lose half of them
                }
            }
        } else {
            // Iterate over all tiles to find those matching the dice roll
            for (int tileId = 0; tileId < 19; ++tileId) {
                if (board.getTileAtIndex(tileId).getdiceNumber() == diceRoll) {
                    Resources::ResourceType resource = board.getTileAtIndex(tileId).getType();
                    std::cout << "Tile ID: " << tileId << " produces resource " << Resources::resourceTypeToString(resource) << std::endl;

                    // Check settlements around the tile and distribute resources accordingly
                    for (Settlement& settlement : board.getSettlements()) {
                        for (int settlementTiles : board.getTilesAroundSettlement(settlement)) {
                            if (settlementTiles == tileId) {
                                for (Player& player : board.getPlayers()) {
                                    if (player.getName() == settlement.getPlayerId()) {
                                        if (settlement.isCity()) {
                                            player.addResource(resource, 2, board); // Cities receive 2 resources
                                            std::cout << "Player " << player.getName() << " receives 2 of " << Resources::resourceTypeToString(resource) << std::endl;
                                        } else {
                                            player.addResource(resource, 1, board); // Settlements receive 1 resource
                                            std::cout << "Player " << player.getName() << " receives 1 of " << Resources::resourceTypeToString(resource) << std::endl;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void Player::trade(Player& other, const std::string& giveItem, const std::string& getItem, int giveAmount, int getAmount, Board& board) {
        std::cout << getName() << " trades " << giveAmount << " " << giveItem << " with " << other.getName() << " for " << getAmount << " " << getItem << std::endl;

        // Determine if the items being traded are resources or development cards
        Resources::ResourceType giveResource = Resources::stringToResourceType(giveItem);
        Resources::ResourceType getResource = Resources::stringToResourceType(getItem);

        DevelopmentCardType giveCardType = DevelopmentCard::stringToDevelopmentCardType(giveItem);
        DevelopmentCardType getCardType = DevelopmentCard::stringToDevelopmentCardType(getItem);

        if (giveResource != Resources::ResourceType::UNKNOWN && getResource != Resources::ResourceType::UNKNOWN) {
            // Trade resources
            if (getResourceCount(giveResource) >= giveAmount && other.getResourceCount(getResource) >= getAmount) {
                removeResource(giveResource, giveAmount, board);
                other.addResource(giveResource, giveAmount, board);
                addResource(getResource, getAmount, board);
                other.removeResource(getResource, getAmount, board);
            } else {
                std::cout << "Not enough resources to trade.\n";
            }
        } else if (giveCardType != DevelopmentCardType::UNKNOWN && getCardType != DevelopmentCardType::UNKNOWN) {
            // Trade development cards for development cards
            int tradedCount = 0;

            while (tradedCount < giveAmount) {
                auto giveCardIt = std::find_if(developmentCards.begin(), developmentCards.end(), [&](const DevelopmentCard& card) {
                    return card.getType() == giveCardType;
                });

                auto getCardIt = std::find_if(other.developmentCards.begin(), other.developmentCards.end(), [&](const DevelopmentCard& card) {
                    return card.getType() == getCardType;
                });

                if (giveCardIt != developmentCards.end() && getCardIt != other.developmentCards.end()) {
                    std::cout << "Removing " << giveItem << " from " << getName() << std::endl;
                    giveCardIt = developmentCards.erase(giveCardIt);
                    std::cout << "Adding " << giveItem << " to " << other.getName() << std::endl;
                    other.developmentCards.push_back(DevelopmentCard(giveCardType));

                    std::cout << "Removing " << getItem << " from " << other.getName() << std::endl;
                    getCardIt = other.developmentCards.erase(getCardIt);
                    std::cout << "Adding " << getItem << " to " << getName() << std::endl;
                    developmentCards.push_back(DevelopmentCard(getCardType));

                    // Update knights count if trading knight cards
                    if (giveCardType == DevelopmentCardType::KNIGHT) {
                        other.knights++;
                        this->knights--;
                    } else if (getCardType == DevelopmentCardType::KNIGHT) {
                        other.knights--;
                        this->knights++;
                    }

                    tradedCount++;
                } else {
                    std::cout << "Not enough development cards to trade.\n";
                    break;
                }
            }

            checkLargestArmy(board); // Check and update largest army status
            board.updatePlayer(other); // Update other player's status on the board
            board.updatePlayer(*this); // Update this player's status on the board

        } else if (giveCardType != DevelopmentCardType::UNKNOWN && getResource != Resources::ResourceType::UNKNOWN) {
            // Trade development cards for resources
            auto giveCardIt = developmentCards.begin();
            int tradedCount = 0;

            this->addResource(getResource, getAmount, board);
            other.removeResource(getResource, getAmount, board);

            while (tradedCount < giveAmount && giveCardIt != developmentCards.end()) {
                if (giveCardIt->getType() == giveCardType) {
                    std::cout << "Removing " << giveItem << " from " << getName() << std::endl;
                    giveCardIt = developmentCards.erase(giveCardIt);
                    std::cout << "Adding " << giveItem << " to " << other.getName() << std::endl;
                    other.developmentCards.push_back(DevelopmentCard(giveCardType));

                    // Update knights count if trading knight cards
                    if (giveCardType == DevelopmentCardType::KNIGHT) {
                        other.knights++;
                        this->knights--;
                    }

                    tradedCount++;
                } else {
                    ++giveCardIt;
                }
            }
            board.updatePlayer(other); // Update other player's status on the board
            board.updatePlayer(*this); // Update this player's status on the board
            checkLargestArmy(board); // Check and update largest army status


        } else if (getCardType != DevelopmentCardType::UNKNOWN && giveResource != Resources::ResourceType::UNKNOWN) {
            // Trade resources for development cards
            auto getCardIt = other.developmentCards.begin();
            int tradedCount = 0;

            this->removeResource(giveResource, giveAmount, board);
            other.addResource(giveResource, giveAmount, board);

            while (tradedCount < getAmount && getCardIt != other.developmentCards.end()) {
                if (getCardIt->getType() == getCardType) {
                    std::cout << "Removing " << getItem << " from " << other.getName() << std::endl;
                    getCardIt = other.developmentCards.erase(getCardIt);
                    std::cout << "Adding " << getItem << " to " << getName() << std::endl;
                    this->developmentCards.push_back(DevelopmentCard(getCardType));

                    // Update knights count if trading knight cards
                    if (getCardType == DevelopmentCardType::KNIGHT) {
                        other.knights--;
                        this->knights++;
                    }

                    tradedCount++;
                } else {
                    ++getCardIt;
                }
            }

            checkLargestArmy(board); // Check and update largest army status
            board.updatePlayer(other); // Update other player's status on the board
            board.updatePlayer(*this); // Update this player's status on the board
        } else {
            std::cout << "Invalid trade items.\n";
        }
    }

    void Player::printPoints() const {
    std::cout << playerId << " has " << points << " points." << std::endl; // Output player's points
}

    std::string Player::getName() const {
        return playerId; // Return player's ID
    }

    int Player::getPoints() const {
        return points; // Return player's points
    }

    void Player::setPoints(int points) {
        this->points = points; // Set player's points
    }

    bool Player::getHasLargestArmy() {
        return this->hasLargestArmy; // Return whether the player has the largest army
    }

    int Player::getKnights() {
        return knights; // Return number of knight cards the player has
    }

    void Player::setKnights(int num) {
        this->knights = num; // Set number of knight cards the player has
    }

    void Player::placeSettlement(int vertice, Board& board) {
        if (vertice > 53 || vertice < 0) {
            std::cout << "not valid vertice"; // Check if vertex ID is valid
        }
        if (board.isSettlementAvailable(playerId, vertice)) {
            if (board.getNumSettlements(this->playerId) >= 2 && this->hasResourcesForSettlementBuilding()) {
                // Place settlement if player has enough settlements and resources
                board.placeSettlement(playerId, vertice);
                std::cout << playerId << " Successfully placed a settlement on vertice: " << vertice << std::endl;
                points++;
                this->removeResourcesForSettlementBuilding();
                board.updatePlayer(*this);
            } else {
                if (board.getNumSettlements(this->playerId) < 2) {
                    // Place settlement if player has fewer than 2 settlements
                    board.placeSettlement(playerId, vertice);
                    std::cout << playerId << " Successfully placed a settlement on vertice: " << vertice << std::endl;
                    points++;
                    // Distribute resources based on tiles around the settlement
                    std::vector<int> tileIds = board.getVertexToTiles()[vertice];
                    for (int tileId : tileIds) {
                        Resources::ResourceType resourceType = board.getTileAtIndex(tileId).getType();
                        this->addResource(resourceType, 1, board); // Add resource to player
                    }
                    board.updatePlayer(*this);
                } else {
                    std::cout << "Not enough resources for building settlement.\n";
                }
            }
        } else {
            std::cout << "this vertice is occupied\n" << std::endl;
        }
    }

    void Player::placeRoad(int fromVertice, int toVertice, Board& board) {
        if (fromVertice > 53 || toVertice > 53 || fromVertice < 0 || toVertice < 0) {
            std::cout << "not valid vertice"; // Check if vertex IDs are valid
        }
        if (board.isRoadAvailable(playerId, fromVertice, toVertice)) {
            if (board.getNumRoads(this->playerId) >= 2 && this->hasResourcesForRoadBuilding() && !this->roadBuildingCardActivated) {
                // Place road if player has enough roads, resources, and road building card is not activated
                board.placeRoad(playerId, fromVertice, toVertice);
                std::cout << playerId << " Successfully placed a road fromVertice: " << fromVertice <<
                    " toVertice: " << toVertice << std::endl;
                this->removeResourcesForRoadBuilding();
                board.updatePlayer(*this);
            } else {
                if (board.getNumRoads(this->playerId) < 2 || this->roadBuildingCardActivated) {
                    // Place road if player has fewer than 2 roads or road building card is activated
                    board.placeRoad(playerId, fromVertice, toVertice);
                    this->roadBuildingCardActivated = false;
                    std::cout << playerId << " Successfully placed a road fromVertice: " << fromVertice <<
                        " toVertice: " << toVertice << std::endl;
                    board.updatePlayer(*this);
                } else {
                    std::cout << "Not enough resources for building road.\n";
                }
            }
        }
    }

    bool Player::placeCity(int vertice, Board& board) {
        if (vertice > 53 || vertice < 0) {
            std::cout << "not valid vertice"; // Check if vertex ID is valid
        }

        // Iterate through settlements to find the one to upgrade
        for (Settlement& settlement : board.getSettlements()) {
            if (settlement.getVerticeId() == vertice) {
                if (!this->hasResourcesForCityBuilding()) {
                    std::cout << "Player " << playerId << " does not have enough resources to build a city." << std::endl;
                    return false;
                }
                if (settlement.isCity()) {
                    std::cout << "The settlement on vertice " << vertice << " is already a city." << std::endl;
                    return false;
                }
                if (this->playerId != settlement.getPlayerId()) {
                    std::cout << "Player " << playerId << " does not own the settlement on vertice " << vertice << "." << std::endl;
                    return false;
                }
                // Upgrade settlement to city if all conditions are met
                settlement.upgradeToCity();
                this->removeResourcesForCityBuilding();
                std::cout << playerId << " successfully placed a city on vertice: " << vertice << std::endl;
                points++;
                return true;
            }
        }
        // If no settlement matches the given vertice
        std::cout << "No settlement found on vertice " << vertice << "." << std::endl;
        return false;
    }

    bool Player::hasResourcesForRoadBuilding() const {
        // Check if player has enough wood and brick resources for road building
        int wood = 0, brick = 0;
        for (const std::pair<Resources::ResourceType, int>& resource : resources) {
            if (resource.first == Resources::ResourceType::WOOD) {
                wood = resource.second;
            }
            if (resource.first == Resources::ResourceType::BRICK) {
                brick = resource.second;
            }
        }
        return (wood >= 1 && brick >= 1);
    }

    bool Player::hasResourcesForCityBuilding() const {
        // Check if player has enough ore and grain resources for city building
        int ore = 0, grain = 0;
        for (const std::pair<Resources::ResourceType, int>& resource : resources) {
            if (resource.first == Resources::ResourceType::ORE) {
                ore = resource.second;
            }
            if (resource.first == Resources::ResourceType::GRAIN) {
                grain = resource.second;
            }
        }
        return (ore >= 3 && grain >= 2);
    }

    bool Player::hasResourcesForSettlementBuilding() const {
        // Check if player has enough wood, brick, grain, and wool resources for settlement building
        int wood = 0, grain = 0, wool = 0, brick = 0;
        for (const std::pair<Resources::ResourceType, int>& resource : resources) {
            if (resource.first == Resources::ResourceType::WOOD) {
                wood = resource.second;
            }
            if (resource.first == Resources::ResourceType::BRICK) {
                brick = resource.second;
            }
            if (resource.first == Resources::ResourceType::GRAIN) {
                grain = resource.second;
            }
            if (resource.first == Resources::ResourceType::WOOL) {
                wool = resource.second;
            }
        }
        return (wood >= 1 && brick >= 1 && grain >= 1 && wool >= 1);
    }

    void Player::removeResourcesForRoadBuilding() {
        // Remove wood and brick resources for road building
        for (std::pair<Resources::ResourceType, int>& resource : resources) {
            if (resource.first == Resources::ResourceType::WOOD && resource.second > 0) {
                resource.second--;
            }
            if (resource.first == Resources::ResourceType::BRICK && resource.second > 0) {
                resource.second--;
            }
        }
    }
    bool Player::hasResourcesForDevelopmentCard() const {
        // Remove ore, grain and wool resources for development card building
        int ore = 0, grain = 0, wool = 0;
        for (const std::pair<Resources::ResourceType, int>& resource : resources) {
            if (resource.first == Resources::ResourceType::ORE) {
                ore = resource.second;
            }
            if (resource.first == Resources::ResourceType::GRAIN) {
                grain = resource.second;
            }
            if (resource.first == Resources::ResourceType::WOOL) {
                wool = resource.second;
            }
        }
        return (ore >= 1 && grain >= 1 && wool >=1); 
    }

    void Player::removeResourcesForCityBuilding() {
        // Remove ore and grain resources for city building
        for (std::pair<Resources::ResourceType, int>& resource : resources) {
            if (resource.first == Resources::ResourceType::ORE && resource.second > 0) {
                resource.second -= 3;
            }
            if (resource.first == Resources::ResourceType::GRAIN && resource.second > 0) {
                resource.second -= 2;
            }
        }
    }

    void Player::removeResourcesForSettlementBuilding() {
        // Remove wood, brick, grain, and wool resources for settlement building
        for (std::pair<Resources::ResourceType, int>& resource : resources) {
            if (resource.first == Resources::ResourceType::WOOD && resource.second > 0) {
                resource.second--;
            }
            if (resource.first == Resources::ResourceType::GRAIN && resource.second > 0) {
                resource.second--;
            }
            if (resource.first == Resources::ResourceType::WOOL && resource.second > 0) {
                resource.second--;
            }
            if (resource.first == Resources::ResourceType::BRICK && resource.second > 0) {
                resource.second--;
            }
        }
    }
        void Player::removeResourcesForDevelopmentCard() {
        // Remove resources (grain, wool, ore) for purchasing a development card
        for (std::pair<Resources::ResourceType, int>& resource : resources) {
            if (resource.first == Resources::ResourceType::GRAIN && resource.second > 0) {
                resource.second--;
            }
            if (resource.first == Resources::ResourceType::WOOL && resource.second > 0) {
                resource.second--;
            }
            if (resource.first == Resources::ResourceType::ORE && resource.second > 0) {
                resource.second--;
            }
        }
    }

    void Player::addResource(Resources::ResourceType resource, int quantity, Board& board) {
        // Add specified quantity of a resource to the player's inventory
        for (std::pair<Resources::ResourceType, int>& res : resources) {
            if (res.first == resource) {
                res.second += quantity;
                // Output message indicating the added resources
                std::cout << "Added " << quantity << " " << Resources::resourceTypeToString(resource) 
                        << " to player " << playerId << std::endl;
                board.updatePlayer(*this); // Update player information in the board
                break;
            }
        }
    }

    int Player::getTotalResources() {
        // Calculate total number of resources the player possesses
        int totalResources = 0;
        for (int i = 0; i < 5; ++i) {
            totalResources += resources[i].second; // Accumulate resources
        }
        return totalResources;
    }

    void Player::loseHalfResources() {
        // Player loses half of their resources
        std::cout << playerId << " has to lose half of their resources.\n";
        for (std::pair<Resources::ResourceType, int>& resource : resources) {
            int quantityToLose = std::floor(resource.second / 2.0); // Calculate half of the resource quantity
            resource.second -= quantityToLose; // Subtract half of the resources
            // Output message indicating the lost resources
            std::cout << "Lost " << quantityToLose << " " << Resources::resourceTypeToString(resource.first) << ".\n";
        }
    }

    void Player::buyDevelopmentCard(Board& board) {
        // Attempt to purchase a development card
        if (hasResourcesForDevelopmentCard()) {
            removeResourcesForDevelopmentCard(); // Deduct resources for purchasing a development card
            DevelopmentCard newCard = board.drawDevelopmentCard(); // Draw a development card from the board
            developmentCards.push_back(newCard); // Add the new development card to the player's collection
            board.updatePlayer(*this); // Update player information in the board
        } else {
            std::cout << "Not enough resources to buy a development card.\n";
        }
    }

    bool Player::hasDevelopmentCard() {
        // Check if the player possesses any development cards
        return !developmentCards.empty();
    }

    void Player::playDevelopmentCard(DevelopmentCardType cardType, Board& board) {
        // Play a specific development card type
        for (std::vector<DevelopmentCard>::iterator it = developmentCards.begin(); it != developmentCards.end(); ++it) {
            if (it->getType() == cardType) {
                // Implement the specific effect of each card type
                if (cardType == DevelopmentCardType::KNIGHT) {
                    std::cout << "Knight card played: move the robber.\n";
                    this->knights++; // Increment the count of knight cards played
                    board.updatePlayer(*this); // Update player information in the board
                    checkLargestArmy(board); // Check if the player now holds the largest army
                } else if (cardType == DevelopmentCardType::ROAD_BUILDING) {
                    std::cout << "Road Building card played: you can now place 2 roads.\n";
                    this->roadBuildingCardActivated = true; // Activate road building card ability
                    // Prompt player to place their first road
                    int fromVertice, toVertice;
                    std::cout << playerId << " Where do you want to place your first road.\n fromVertice: ";
                    std::cin >> fromVertice;
                    std::cout << " toVertice\n";
                    std::cin >> toVertice;
                    this->placeRoad(fromVertice, toVertice, board); // Place the first road
                    // Prompt player to place their second road
                    std::cout << " and from the second road.\n fromVertice: ";
                    std::cin >> fromVertice;
                    std::cout << " toVertice:\n";
                    std::cin >> toVertice;
                    this->placeRoad(fromVertice, toVertice, board); // Place the second road
                    developmentCards.erase(it); // Remove the road building card from the player's deck
                    std::cout << "Road building card removed from player's deck.\n";
                    board.updatePlayer(*this); // Update player information in the board
                } else if (cardType == DevelopmentCardType::YEAR_OF_PLENTY) {
                    std::cout << "Year of Plenty card played: draw 2 resource cards of your choice from the bank.\n";
                    this->drawTwoResourceCards(board); // Execute the Year of Plenty card effect
                    developmentCards.erase(it); // Remove the Year of Plenty card from the player's deck
                    std::cout << "Year Of Plenty card removed from player's deck.\n";
                    board.updatePlayer(*this); // Update player information in the board
                } else if (cardType == DevelopmentCardType::MONOPOLY) {
                    std::cout << "Monopoly card played: claim all resource cards of a specific declared type.\n";
                    this->claimAllResourceCards(board); // Execute the Monopoly card effect
                    developmentCards.erase(it); // Remove the Monopoly card from the player's deck
                    std::cout << "Monopoly card removed from player's deck.\n";
                    board.updatePlayer(*this); // Update player information in the board
                } else if (cardType == DevelopmentCardType::VICTORY_POINT) {
                    std::cout << "Victory Point card played: 1 additional Victory Point added to your total.\n";
                    this->points++; // Increment the player's victory points
                }
                break;
            }
        }
    }

    void Player::drawTwoResourceCards(Board& board) {
        // Execute the Year of Plenty card effect: draw 2 resource cards of player's choice from the bank
        Resources::ResourceType choice1, choice2;
        // Prompt player to choose the first resource card
        std::cout << "Choose the first resource card (type '1' for grain, '2' for wool, '3' for ore, '4' for brick, '5' for wood): ";
        int input1;
        std::cin >> input1;
        // Convert input to ResourceType
        switch (input1) {
            case 1:
                choice1 = Resources::ResourceType::GRAIN;
                break;
            case 2:
                choice1 = Resources::ResourceType::WOOL;
                break;
            case 3:
                choice1 = Resources::ResourceType::ORE;
                break;
            case 4:
                choice1 = Resources::ResourceType::BRICK;
                break;
            case 5:
                choice1 = Resources::ResourceType::WOOD;
                break;
            default:
                std::cout << "Invalid input. Please choose again.\n";
                return; // Exit the method if input is invalid
        }
        // Prompt player to choose the second resource card
        std::cout << "Choose the second resource card (type '1' for grain, '2' for wool, '3' for ore, '4' for brick, '5' for wood): ";
        int input2;
        std::cin >> input2;
        // Convert input to ResourceType
        switch (input2) {
            case 1:
                choice2 = Resources::ResourceType::GRAIN;
                break;
            case 2:
                choice2 = Resources::ResourceType::WOOL;
                break;
            case 3:
                choice2 = Resources::ResourceType::ORE;
                break;
            case 4:
                choice2 = Resources::ResourceType::BRICK;
                break;
            case 5:
                choice2 = Resources::ResourceType::WOOD;
                break;
            default:
                std::cout << "Invalid input. Please choose again.\n";
                return; // Exit the method if input is invalid
        }
        // Add the chosen resource cards to the player's hand
        this->addResource(choice1, 1, board);
        this->addResource(choice2, 1, board);
        std::cout << "Resource cards added to your hand.\n";
    }

    void Player::claimAllResourceCards(Board& board) {
        // Execute the Monopoly card effect: claim all resource cards of a specific declared type from other players
        Resources::ResourceType choice;
        // Prompt player to choose the resource type to claim
        std::cout << "Choose the resource type to claim (type '1' for grain, '2' for wool, '3' for ore, '4' for brick, '5' for wood): ";
        int input;
        std::cin >> input;
        // Convert input to ResourceType
        switch (input) {
            case 1:
                choice = Resources::ResourceType::GRAIN;
                break;
            case 2:
                choice = Resources::ResourceType::WOOL;
                break;
            case 3:
                choice = Resources::ResourceType::ORE;
                break;
            case 4:
                choice = Resources::ResourceType::BRICK;
                break;
            case 5:
                choice = Resources::ResourceType::WOOD;
                break;
            default:
                std::cout << "Invalid input. Please choose again.\n";
                return; // Exit the method if input is invalid
        }
        // Loop through all players to claim the chosen resource cards
        for (Player& otherPlayer : board.getPlayers()) {
            if (otherPlayer.getName() != this->getName()) { // Exclude the current player
                int resourceCount = otherPlayer.getResourceCount(choice); // Get the number of resources of the chosen type from the other player
                if (resourceCount > 0) {
                    otherPlayer.removeResource(choice, resourceCount, board); // Transfer the claimed resource cards from the other player
                    this->addResource(choice, resourceCount, board); // Add the claimed resource cards to the current player
                }
            }
        }
        // Update all players' information in the board after claiming resources
        for (Player& player : board.getPlayers()) {
            board.updatePlayer(player);
        }
        std::cout << "Resource cards claimed from other players.\n";
    }

    int Player::getResourceCount(Resources::ResourceType resourceType) const {
        // Retrieve the count of a specific resource type in the player's inventory
        for (const std::pair<Resources::ResourceType, int>& resource : resources) {
            if (resource.first == resourceType) {
                return resource.second;
            }
        }
        return 0; // Return 0 if the resource type is not found
    }

    // Implementation of removeResource method
    void Player::removeResource(Resources::ResourceType resourceType, int quantity, Board& board) {
        // Iterate through the player's resources
        for (std::pair<Resources::ResourceType, int>& resource : resources) {
            // Check if the resource type matches
            if (resource.first == resourceType) {
                // Ensure the player has enough resources to remove
                if (resource.second >= quantity) {
                    resource.second -= quantity; // Deduct the specified quantity
                    // Output message indicating the removed resources
                    std::cout << "Removed " << quantity << " " << Resources::resourceTypeToString(resourceType)
                            << " from " << playerId << "'s inventory.\n";
                    board.updatePlayer(*this); // Update player information in the board
                } else {
                    // Output message if player does not have enough resources
                    std::cout << playerId << " doesn't have enough " << Resources::resourceTypeToString(resourceType)
                            << " to remove.\n";
                }
                return; // Exit the method after removing the resources
            }
        }
        // Output message if player does not possess the specified resource type
        std::cout << playerId << " doesn't have any " << Resources::resourceTypeToString(resourceType) << " to remove.\n";
    }

    void Player::incrementTurnsPlayed() {
        turnsPlayed++; // Increment the turns played by the player
    }

    void Player::printStats(Board& board) const {
        // Print player statistics
        // 1. Print player name
        std::cout << "Player Name: " << playerId << std::endl;

        // 2. Print player points
        std::cout << "Points: " << points << std::endl;

        // 3. Print player's resources
        std::cout << "Resources:" << std::endl;
        bool hasResources = false;
        for (const std::pair<Resources::ResourceType, int>& resource : resources) {
            if (resource.second > 0) {
                std::cout << Resources::resourceTypeToString(resource.first) << ": " << resource.second << std::endl;
                hasResources = true;
            }
        }
        if (!hasResources) {
            std::cout << "No resources.\n";
        }

        // 4. Print player's development cards
        std::cout << "Development Cards:" << std::endl;
        bool hasDevelopmentCards = false;
        for (DevelopmentCard card : developmentCards) {
            std::cout << "Type: " << card.developmentCardTypeToString(card.getType()) << std::endl;
            hasDevelopmentCards = true;
        }
        if (!hasDevelopmentCards) {
            std::cout << "No development cards.\n";
        }

        // 5. Print number of settlements and their vertices
        int numSettlements = 0;
        std::cout << "Settlements:" << std::endl;
        for (Settlement& settlement : board.getSettlements()) {
            if (settlement.getPlayerId() == playerId) {
                numSettlements++;
                std::cout << "Vertex: " << settlement.getVerticeId() << std::endl;
            }
        }
        if (numSettlements == 0) {
            std::cout << "No settlements.\n";
        }

        // 6. Print roads and their edges
        int numRoads = 0;
        std::cout << "Roads:" << std::endl;
        for (Road road : board.getRoads()) {
            if (road.getPlayerId() == playerId) {
                numRoads++;
                std::cout << "From Vertex: " << road.getVertices().first << " to Vertex: " << road.getVertices().second << std::endl;
            }
        }
        if (numRoads == 0) {
            std::cout << "No Roads.\n";
        }

        // 7. Print number of cities and their vertices
        int numCities = 0;
        std::cout << "Cities:" << std::endl;
        for (Settlement& settlement : board.getSettlements()) {
            if (settlement.getPlayerId() == playerId && settlement.isCity()) {
                numCities++;
                std::cout << "Vertex: " << settlement.getVerticeId() << std::endl;
            }
        }
        if (numCities == 0) {
            std::cout << "No cities.\n";
        }
    }

    void Player::checkLargestArmy(Board& board) {
        Player* newPlayerWithLargestArmy = nullptr;
        int maxKnights = 0;

        // Iterate through all players on the board
        for (Player& player : board.getPlayers()) {
            int playerKnights = player.getKnights();

            // Only consider players with at least 3 knights
            if (playerKnights >= 3 && playerKnights > maxKnights) {
                maxKnights = playerKnights;
                newPlayerWithLargestArmy = &player;
            }
        }

        // Check if there is a change in the player with the largest army
        if (newPlayerWithLargestArmy != playerWithLargestArmy) {
            if (playerWithLargestArmy) {
                // Remove points and update status for the previous holder
                std::cout << playerWithLargestArmy->getName() << " loses Largest Army bonus points.\n";
                playerWithLargestArmy->points -= 2;
                playerWithLargestArmy->hasLargestArmy = false;
            }

            if (newPlayerWithLargestArmy) {
                // Add points and update status for the new holder
                std::cout << newPlayerWithLargestArmy->getName() << " gains Largest Army bonus points.\n";
                newPlayerWithLargestArmy->points += 2;
                newPlayerWithLargestArmy->hasLargestArmy = true;
            }

            // Update the playerWithLargestArmy pointer
            playerWithLargestArmy = newPlayerWithLargestArmy;

            // No need to call updatePlayer since we are directly modifying the objects
        }
    }
}

