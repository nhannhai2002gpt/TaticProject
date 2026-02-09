#ifndef PROPERTY_CONTAINER_H
#define PROPERTY_CONTAINER_H

#include "Property.h"
#include <map>
#include <memory>
#include <vector>

// Container to manage multiple properties (static, dynamic, maintenance, custom)
class PropertyContainer {
public:
    PropertyContainer() = default;

    // Add property
    void addProperty(const std::string& key, const Property& property) {
        properties_[key] = std::make_shared<Property>(property);
    }

    // Get property by key
    std::shared_ptr<Property> getProperty(const std::string& key) {
        auto it = properties_.find(key);
        if (it != properties_.end()) {
            return it->second;
        }
        return nullptr;
    }

    const std::shared_ptr<Property> getProperty(const std::string& key) const {
        auto it = properties_.find(key);
        if (it != properties_.end()) {
            return it->second;
        }
        return nullptr;
    }

    // Set property value
    template<typename T>
    void setPropertyValue(const std::string& key, const T& value) {
        auto prop = getProperty(key);
        if (prop) {
            prop->setValue(value);
        } else {
            throw std::runtime_error("Property '" + key + "' not found");
        }
    }

    // Get property value
    template<typename T>
    T getPropertyValue(const std::string& key) const {
        auto prop = getProperty(key);
        if (prop && prop->hasValue()) {
            return prop->getValueAs<T>();
        }
        throw std::runtime_error("Property '" + key + "' not found or has no value");
    }

    // Get all properties
    const std::map<std::string, std::shared_ptr<Property>>& getAllProperties() const {
        return properties_;
    }

    // Remove property
    bool removeProperty(const std::string& key) {
        return properties_.erase(key) > 0;
    }

    // Check if property exists
    bool hasProperty(const std::string& key) const {
        return properties_.find(key) != properties_.end();
    }

    // Get all property keys
    std::vector<std::string> getPropertyKeys() const {
        std::vector<std::string> keys;
        for (const auto& pair : properties_) {
            keys.push_back(pair.first);
        }
        return keys;
    }

    // Clear all properties
    void clear() {
        properties_.clear();
    }

    // Get property count
    size_t getPropertyCount() const {
        return properties_.size();
    }

private:
    std::map<std::string, std::shared_ptr<Property>> properties_;
};

#endif // PROPERTY_CONTAINER_H