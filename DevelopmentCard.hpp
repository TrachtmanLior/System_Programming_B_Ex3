// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#ifndef DEVELOPMENT_CARD_HPP
#define DEVELOPMENT_CARD_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <random>

namespace ariel {

    enum class DevelopmentCardType {
        KNIGHT,              // Knight card type
        VICTORY_POINT,       // Victory point card type
        ROAD_BUILDING,       // Road building card type
        MONOPOLY,            // Monopoly card type
        YEAR_OF_PLENTY,      // Year of plenty card type
        UNKNOWN              // Default unknown type
    };

    class DevelopmentCard {
    private:
        DevelopmentCardType type;   // Type of the development card
        std::string description;    // Description of the development card

        void setDescription();      // Helper method to set the description based on the card type

    public:
        DevelopmentCard(DevelopmentCardType type);  // Constructor with type parameter
        DevelopmentCardType getType() const;         // Getter for the development card type
        std::string getDescription() const;          // Getter for the description of the development card
        void printCardDetails() const;               // Method to print details of the development card
        static std::vector<DevelopmentCard> initializeDeck();        // Static method to initialize a deck of development cards
        static void shuffleDeck(std::vector<DevelopmentCard>& deck); // Static method to shuffle a deck of development cards
        static DevelopmentCard drawCard(std::vector<DevelopmentCard>& deck); // Static method to draw a card from a deck
        static DevelopmentCardType stringToDevelopmentCardType(const std::string& cardString); // Static method to convert a string to DevelopmentCardType enum
        static bool isValidDevelopmentCardType(const std::string& card); // Static method to check if a string is a valid DevelopmentCardType
        std::string developmentCardTypeToString(DevelopmentCardType type); // Method to convert DevelopmentCardType enum to string
    };

} // namespace ariel

#endif // DEVELOPMENT_CARD_HPP
