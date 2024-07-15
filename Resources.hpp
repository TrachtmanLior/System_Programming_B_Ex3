// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <vector>
#include <string>

namespace ariel {
    class Resources {
    private:
        std::vector<std::string> resourceTypes;   // Vector to hold resource type names
        std::vector<int> resourceNumbers;         // Vector to hold resource numbers

    public:
        // Enum defining resource types
        enum class ResourceType {
            GRAIN,
            WOOL,
            ORE,
            WOOD,
            BRICK,
            DESERT,
            UNKNOWN
        };

        // Function to convert ResourceType enum to string
        static std::string resourceTypeToString(ResourceType resourceType) {
            switch (resourceType) {
                case ResourceType::GRAIN:
                    return "Grain";
                case ResourceType::WOOL:
                    return "Wool";
                case ResourceType::ORE:
                    return "Ore";
                case ResourceType::WOOD:
                    return "Wood";
                case ResourceType::BRICK:
                    return "Brick";
                case ResourceType::DESERT:
                    return "Desert";
                default:
                    return "Unknown";
            }
        }

        Resources();  // Constructor declaration
        static ResourceType stringToResourceType(const std::string& resourceString);  // Method to convert string to ResourceType enum
        std::vector<std::string> distributeResourceTypes();  // Method to distribute resource types
        std::vector<int> distributeResourceNumbers();  // Method to distribute resource numbers
    };
}

#endif // RESOURCES_HPP
