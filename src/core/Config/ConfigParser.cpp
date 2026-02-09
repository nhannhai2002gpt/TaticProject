#include "ConfigParser.h"
#include <stdexcept>
#include <sstream>

// Parse entity definition from XML file
// Note: In production, use proper XML library (like TinyXML2, RapidXML, or pugixml)
// This is simplified version for demonstration
EntityDefinition ConfigParser::parseEntityDefinition(const std::string& /*xmlFilePath*/) {
    EntityDefinition def;
    
    // TODO: Implement actual XML parsing
    // For now, return placeholder
    def.type = "Ship";
    def.category = "CargoShip";
    def.description = "Cargo shipping vessel";
    
    return def;
}

// Parse entity instance from XML file
std::map<std::string, std::any> ConfigParser::parseEntityInstance(const std::string& /*xmlFilePath*/) {
    std::map<std::string, std::any> instance;
    
    // TODO: Implement actual XML parsing
    // For now, return placeholder
    instance["id"] = std::string("SHIP-001");
    instance["name"] = std::string("Test Ship");
    
    return instance;
}

// Parse system configuration from JSON file
std::map<std::string, std::string> ConfigParser::parseSystemConfig(const std::string& /*jsonFilePath*/) {
    std::map<std::string, std::string> config;
    
    // TODO: Implement actual JSON parsing
    // For now, return placeholder
    config["app_name"] = "TaticProject";
    config["version"] = "1.0.0";
    
    return config;
}

// Helper: Parse property metadata
PropertyMetadata ConfigParser::parsePropertyMetadata(const std::string& typeStr,
                                                     const std::string& unitStr,
                                                     const std::string& description) {
    PropertyMetadata meta(typeStr, unitStr);
    meta.setDescription(description);
    return meta;
}

// Helper: Parse value from string to std::any
std::any ConfigParser::parseValue(const std::string& type, const std::string& valueStr) {
    if (type == "double" || type == "float") {
        return std::any(std::stod(valueStr));
    } else if (type == "int") {
        return std::any(std::stoi(valueStr));
    } else if (type == "string") {
        return std::any(valueStr);
    } else if (type == "bool") {
        return std::any(valueStr == "true" || valueStr == "1");
    }
    return std::any(valueStr);
}