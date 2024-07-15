// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#include "Resources.hpp"
#include <algorithm>
#include <random>
#include <ctime>

namespace ariel {
    // Constructor initializes the resources with specified quantities
    Resources::Resources() {
        resourceTypes = {"Wool", "Wool", "Wool", "Wool",
                         "Brick", "Brick", "Brick",
                         "Wood", "Wood", "Wood", "Wood",
                         "Grain", "Grain", "Grain", "Grain",
                         "Ore", "Ore", "Ore",
                         "Desert"};
        
        resourceNumbers = {0, 2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
    }

    // Function to convert string to ResourceType enum
    Resources::ResourceType Resources::stringToResourceType(const std::string& resourceString) {
        if (resourceString == "Grain") return ResourceType::GRAIN;
        if (resourceString == "Wool") return ResourceType::WOOL;
        if (resourceString == "Ore") return ResourceType::ORE;
        if (resourceString == "Wood") return ResourceType::WOOD;
        if (resourceString == "Brick") return ResourceType::BRICK;
        if (resourceString == "Desert") return ResourceType::DESERT;
        return ResourceType::UNKNOWN; // Return UNKNOWN for unrecognized resource types
    }

    // Method to shuffle and distribute resource types
    std::vector<std::string> Resources::distributeResourceTypes() {
        std::shuffle(resourceTypes.begin(), resourceTypes.end(), std::mt19937{std::random_device{}()});
        return resourceTypes;
    }

    // Method to shuffle and distribute resource numbers
    std::vector<int> Resources::distributeResourceNumbers() {
        std::shuffle(resourceNumbers.begin(), resourceNumbers.end(), std::mt19937{std::random_device{}()});
        return resourceNumbers;
    }

} // namespace ariel
