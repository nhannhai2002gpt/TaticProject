#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include <unordered_map>
#include <typeinfo>
#include <any>
#include <vector>
#include <stdexcept>

// Property metadata (unit, min, max, enum values, etc.)
class PropertyMetadata {
public:
    PropertyMetadata() = default;
    
    PropertyMetadata(const std::string& typeStr, const std::string& unitStr = "")
        : typeString(typeStr), unit(unitStr) {}

    std::string typeString;        // "double", "int", "string", "enum", etc.
    std::string unit;              // "m", "knots", "%", "tonnes", etc.
    std::string description;       // User description
    std::any minValue;             // Min constraint
    std::any maxValue;             // Max constraint
    std::vector<std::string> enumValues; // For enum type
    std::any defaultValue;         // Default value

    void setDescription(const std::string& desc) {
        description = desc;
    }

    void setMinValue(const std::any& val) {
        minValue = val;
    }

    void setMaxValue(const std::any& val) {
        maxValue = val;
    }

    void addEnumValue(const std::string& val) {
        enumValues.push_back(val);
    }

    void setDefaultValue(const std::any& val) {
        defaultValue = val;
    }
};

// Generic property with typed value and metadata
class Property {
public:
    // Default constructor - REQUIRED for std::map
    Property() 
        : name_(""), metadata_(PropertyMetadata()), value_(std::any()) {}

    // Constructor with parameters
    Property(const std::string& name, const PropertyMetadata& metadata = PropertyMetadata())
        : name_(name), metadata_(metadata), value_(std::any()) {}

    // Getters
    const std::string& getName() const {
        return name_;
    }

    const PropertyMetadata& getMetadata() const {
        return metadata_;
    }

    const std::any& getValue() const {
        return value_;
    }

    // Setters
    void setValue(const std::any& val) {
        value_ = val;
    }

    template<typename T>
    void setValue(const T& val) {
        value_ = std::any(val);
    }

    // Generic getter with type check
    template<typename T>
    T getValueAs() const {
        try {
            return std::any_cast<T>(value_);
        } catch (const std::bad_any_cast& e) {
            throw std::runtime_error("Property '" + name_ + "': Invalid type cast");
        }
    }

    // Check if property has value
    bool hasValue() const {
        return value_.has_value();
    }

    // Update metadata
    void setMetadata(const PropertyMetadata& meta) {
        metadata_ = meta;
    }

private:
    std::string name_;
    PropertyMetadata metadata_;
    std::any value_;
};

#endif // PROPERTY_H