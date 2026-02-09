#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include "../Entity/Property.h"
#include <string>
#include <vector>
#include <map>
#include <memory>

// Represents entity definition parsed from XML
struct EntityDefinition {
    std::string type;              // "Ship", "Aircraft", etc.
    std::string category;          // "CargoShip", "FighterJet", etc.
    std::string description;
    
    // Property groups
    std::map<std::string, Property> staticProperties;
    std::map<std::string, Property> dynamicProperties;
    std::map<std::string, Property> maintenanceProperties;
    std::map<std::string, Property> customProperties;

    // Helper to get all properties
    std::map<std::string, Property> getAllProperties() const {
        std::map<std::string, Property> all;
        for (const auto& p : staticProperties) all[p.first] = p.second;
        for (const auto& p : dynamicProperties) all[p.first] = p.second;
        for (const auto& p : maintenanceProperties) all[p.first] = p.second;
        for (const auto& p : customProperties) all[p.first] = p.second;
        return all;
    }
};

// Parser for XML entity definitions and instances
class ConfigParser {
public:
    ConfigParser() = default;
    ~ConfigParser() = default;

    // Parse entity definition from XML file
    // Example: config/entities/ship_definitions.xml
    EntityDefinition parseEntityDefinition(const std::string& xmlFilePath);

    // Parse entity instance from XML file
    // Example: config/instances/sample_ship_1.xml
    std::map<std::string, std::any> parseEntityInstance(const std::string& xmlFilePath);

    // Parse system configuration from JSON file
    // Example: config/system_config.json
    std::map<std::string, std::string> parseSystemConfig(const std::string& jsonFilePath);

private:
    // Helper methods
    PropertyMetadata parsePropertyMetadata(const std::string& typeStr, 
                                           const std::string& unitStr,
                                           const std::string& description);
    
    std::any parseValue(const std::string& type, const std::string& valueStr);
};

#endif // CONFIG_PARSER_H