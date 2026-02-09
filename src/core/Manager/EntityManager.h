#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "../Entity/Entity.h"
#include <map>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>

// Manages lifecycle of all entities in the system
class EntityManager {
public:
    EntityManager() = default;
    ~EntityManager() = default;

    // ============ Entity Registration ============
    
    // Add entity to manager
    void addEntity(std::shared_ptr<Entity> entity) {
        if (!entity) {
            throw std::runtime_error("Cannot add null entity");
        }
        std::string id = entity->getId();
        if (entities_.find(id) != entities_.end()) {
            throw std::runtime_error("Entity with id '" + id + "' already exists");
        }
        entity->initialize();
        entities_[id] = entity;
    }

    // Remove entity by id
    bool removeEntity(const std::string& id) {
        auto it = entities_.find(id);
        if (it != entities_.end()) {
            it->second->destroy();
            entities_.erase(it);
            return true;
        }
        return false;
    }

    // ============ Entity Query ============
    
    // Get entity by id
    std::shared_ptr<Entity> getEntity(const std::string& id) {
        auto it = entities_.find(id);
        if (it != entities_.end()) {
            return it->second;
        }
        return nullptr;
    }

    const std::shared_ptr<Entity> getEntity(const std::string& id) const {
        auto it = entities_.find(id);
        if (it != entities_.end()) {
            return it->second;
        }
        return nullptr;
    }

    // Get all entities by type
    std::vector<std::shared_ptr<Entity>> getEntitiesByType(const std::string& type) {
        std::vector<std::shared_ptr<Entity>> result;
        for (const auto& pair : entities_) {
            if (pair.second->getType() == type) {
                result.push_back(pair.second);
            }
        }
        return result;
    }

    // Get all entities by category
    std::vector<std::shared_ptr<Entity>> getEntitiesByCategory(const std::string& category) {
        std::vector<std::shared_ptr<Entity>> result;
        for (const auto& pair : entities_) {
            if (pair.second->getCategory() == category) {
                result.push_back(pair.second);
            }
        }
        return result;
    }

    // Get all entities
    const std::map<std::string, std::shared_ptr<Entity>>& getAllEntities() const {
        return entities_;
    }

    // Get entity count
    size_t getEntityCount() const {
        return entities_.size();
    }

    // ============ Lifecycle Operations ============
    
    // Update all entities
    void updateAll(double deltaTime) {
        for (auto& pair : entities_) {
            if (pair.second->getLifecycleState() != EntityLifecycleState::Deleted) {
                pair.second->update(deltaTime);
                pair.second->updateLastModifiedTime();
            }
        }
    }

    // Enter maintenance for entity
    bool enterMaintenance(const std::string& id) {
        auto entity = getEntity(id);
        if (entity) {
            entity->enterMaintenance();
            return true;
        }
        return false;
    }

    // Exit maintenance for entity
    bool exitMaintenance(const std::string& id) {
        auto entity = getEntity(id);
        if (entity) {
            entity->exitMaintenance();
            return true;
        }
        return false;
    }

    // ============ Batch Operations ============
    
    // Apply function to all entities
    void forEachEntity(std::function<void(std::shared_ptr<Entity>)> callback) {
        for (auto& pair : entities_) {
            callback(pair.second);
        }
    }

    // Get entities matching predicate
    std::vector<std::shared_ptr<Entity>> findEntities(
        std::function<bool(const std::shared_ptr<Entity>&)> predicate) {
        std::vector<std::shared_ptr<Entity>> result;
        for (const auto& pair : entities_) {
            if (predicate(pair.second)) {
                result.push_back(pair.second);
            }
        }
        return result;
    }

    // Clear all entities
    void clear() {
        for (auto& pair : entities_) {
            pair.second->destroy();
        }
        entities_.clear();
    }

private:
    std::map<std::string, std::shared_ptr<Entity>> entities_; // id -> Entity
};

#endif // ENTITY_MANAGER_H