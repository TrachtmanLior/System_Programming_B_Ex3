// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#include "DevelopmentCard.hpp"
#include <iostream>

namespace ariel {

    // Constructor initializes the development card type and sets its description
    DevelopmentCard::DevelopmentCard(DevelopmentCardType type)
        : type(type) {
        setDescription(); // Set description based on the card type
    }

    // Sets the description of the development card based on its type
    void DevelopmentCard::setDescription() {
        switch (type) {
            case DevelopmentCardType::KNIGHT:
                description = "Knight card - lets the player move the robber";
                break;
            case DevelopmentCardType::VICTORY_POINT:
                description = "Victory Point card - 1 additional Victory Point is added to the owner's total";
                break;
            case DevelopmentCardType::ROAD_BUILDING:
                description = "Road Building card - player can place 2 roads as if they just built them";
                break;
            case DevelopmentCardType::MONOPOLY:
                description = "Monopoly card - player can claim all resource cards of a specific declared type";
                break;
            case DevelopmentCardType::YEAR_OF_PLENTY:
                description = "Year of Plenty card - the player can draw 2 resource cards of their choice from the bank";
                break;
            default:
                description = "Unknown card type";
                break;
        }
    }

    // Getter for the type of the development card
    DevelopmentCardType DevelopmentCard::getType() const {
        return type;
    }

    // Getter for the description of the development card
    std::string DevelopmentCard::getDescription() const {
        return description;
    }

    // Prints details of the development card (type and description)
    void DevelopmentCard::printCardDetails() const {
        std::cout << "Card Type: " << static_cast<int>(type) << "\n";
        std::cout << "Description: " << description << "\n";
    }

    // Initializes a deck of development cards with preset quantities of each type
    std::vector<DevelopmentCard> DevelopmentCard::initializeDeck() {
        std::vector<DevelopmentCard> deck;

        // Add 14 Knight cards
        for (int i = 0; i < 14; i++) {
            deck.push_back(DevelopmentCard(DevelopmentCardType::KNIGHT));
        }

        // Add 5 Victory Point cards
        for (int i = 0; i < 5; i++) {
            deck.push_back(DevelopmentCard(DevelopmentCardType::VICTORY_POINT));
        }

        // Add 2 Road Building cards
        for (int i = 0; i < 2; i++) {
            deck.push_back(DevelopmentCard(DevelopmentCardType::ROAD_BUILDING));
        }

        // Add 2 Year of Plenty cards
        for (int i = 0; i < 2; i++) {
            deck.push_back(DevelopmentCard(DevelopmentCardType::YEAR_OF_PLENTY));
        }

        // Add 2 Monopoly cards
        for (int i = 0; i < 2; i++) {
            deck.push_back(DevelopmentCard(DevelopmentCardType::MONOPOLY));
        }

        return deck;
    }

    // Shuffles the provided deck of development cards using std::shuffle
    void DevelopmentCard::shuffleDeck(std::vector<DevelopmentCard>& deck) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(deck.begin(), deck.end(), g);
    }

    // Draws a development card from the deck and returns it
    DevelopmentCard DevelopmentCard::drawCard(std::vector<DevelopmentCard>& deck) {
        if (deck.empty()) {
            throw std::runtime_error("Cannot draw a card: deck is empty.");
        }
        DevelopmentCard drawnCard = deck.back();
        deck.pop_back();
        return drawnCard;
    }

    // Converts a string representation of a development card type to its enum value
    DevelopmentCardType DevelopmentCard::stringToDevelopmentCardType(const std::string& cardString) {
        if (cardString == "Knight") return DevelopmentCardType::KNIGHT;
        if (cardString == "Victory Point") return DevelopmentCardType::VICTORY_POINT;
        if (cardString == "Road Building") return DevelopmentCardType::ROAD_BUILDING;
        if (cardString == "Monopoly") return DevelopmentCardType::MONOPOLY;
        if (cardString == "Year of Plenty") return DevelopmentCardType::YEAR_OF_PLENTY;
        return DevelopmentCardType::UNKNOWN; // Default case for unknown types
    }

    // Checks if a string represents a valid development card type
    bool DevelopmentCard::isValidDevelopmentCardType(const std::string& card) {
        if (card == "KNIGHT" || card == "VICTORY_POINT" || card == "ROAD_BUILDING" ||
            card == "MONOPOLY" || card == "YEAR_OF_PLENTY") {
            return true;
        } else {
            return false;
        }
    }

    // Converts a DevelopmentCardType enum value to its corresponding string representation
    std::string DevelopmentCard::developmentCardTypeToString(DevelopmentCardType type) {
        switch (type) {
            case DevelopmentCardType::KNIGHT:
                return "Knight";
            case DevelopmentCardType::VICTORY_POINT:
                return "Victory Point";
            case DevelopmentCardType::ROAD_BUILDING:
                return "Road Building";
            case DevelopmentCardType::MONOPOLY:
                return "Monopoly";
            case DevelopmentCardType::YEAR_OF_PLENTY:
                return "Year of Plenty";
            default:
                return "Unknown";
        }
    }

} // namespace ariel
