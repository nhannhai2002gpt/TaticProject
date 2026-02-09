#ifndef ENTITY_H
#define ENTITY_H

#include "PropertyContainer.h"
#include <string>
#include <memory>
#include <ctime>
#include <chrono>

// Entity lifecycle states
enum class EntityLifecycleState {
    Created,      // Just instantiated
    Operating,    // In active operation
    Maintained,   // Under maintenance
    Deleted       // Marked for deletion
};

// Abstract base class for all entities (Ships, Aircraft, Marine Objects, etc.)
class Entity {
public:
    virtual ~Entity() = default;

    // ============ Lifecycle Methods ============
    
    // Initialize entity (called after construction)
    virtual void initialize() {
        lifecycleState_ = EntityLifecycleState::Created;
        createdAt_ = std::chrono::system_clock::now();
    }

    // Update entity state (called each frame/tick)
    virtual void update(double deltaTime) = 0;

    // Enter maintenance mode
    virtual void enterMaintenance() {
        lifecycleState_ = EntityLifecycleState::Maintained;
    }

    // Exit maintenance mode
    virtual void exitMaintenance() {
        lifecycleState_ = EntityLifecycleState::Operating;
    }

    // Delete entity (cleanup)
    virtual void destroy() {
        lifecycleState_ = EntityLifecycleState::Deleted;
    }

    // ============ Property Access ============
    
    PropertyContainer& getProperties() {
        return properties_;
    }

    const PropertyContainer& getProperties() const {
        return properties_;
    }

    // Convenience method to set property value
    template<typename T>
    void setProperty(const std::string& key, const T& value) {
        properties_.setPropertyValue(key, value);
    }

    // Convenience method to get property value
    template<typename T>
    T getProperty(const std::string& key) const {
        return properties_.getPropertyValue<T>(key);
    }

    // ============ Identity & State ============
    
    const std::string& getId() const {
        return id_;
    }

    void setId(const std::string& id) {
        id_ = id;
    }

    const std::string& getType() const {
        return type_;
    }

    void setType(const std::string& type) {
        type_ = type;
    }

    const std::string& getCategory() const {
        return category_;
    }

    void setCategory(const std::string& category) {
        category_ = category;
    }

    EntityLifecycleState getLifecycleState() const {
        return lifecycleState_;
    }

    // ============ Timestamps ============
    
    auto getCreatedTime() const {
        return createdAt_;
    }

    auto getLastUpdateTime() const {
        return lastUpdatedAt_;
    }

    void updateLastModifiedTime() {
        lastUpdatedAt_ = std::chrono::system_clock::now();
    }

    // ============ Virtual Methods for Subclasses ============
    
    // Serialize entity to string (for persistence)
    virtual std::string serialize() const {
        return "Entity(id=" + id_ + ", type=" + type_ + ")";
    }

    // Deserialize entity from string
    virtual void deserialize(const std::string& /* data */) {
        // To be implemented in subclasses
    }

protected:
    // Protected constructor - only subclasses can instantiate
    Entity(const std::string& id, const std::string& type, const std::string& category)
        : id_(id), type_(type), category_(category),
          lifecycleState_(EntityLifecycleState::Created) {
        createdAt_ = std::chrono::system_clock::now();
        lastUpdatedAt_ = createdAt_;
    }

    std::string id_;                    // Unique identifier
    std::string type_;                  // Entity type ("Ship", "Aircraft", etc.)
    std::string category_;              // Category ("CargoShip", "FighterJet", etc.)
    PropertyContainer properties_;      // All properties (static, dynamic, maintenance, custom)
    EntityLifecycleState lifecycleState_;
    std::chrono::system_clock::time_point createdAt_;
    std::chrono::system_clock::time_point lastUpdatedAt_;
};

#endif // ENTITY_H