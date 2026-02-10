#ifndef SHIPENTITY_H
#define SHIPENTITY_H

#include <string>

class ShipEntity {
public:
    ShipEntity(const std::string& name, int capacity);
    virtual ~ShipEntity();
    std::string getName() const;
    int getCapacity() const;

protected:
    std::string name;
    int capacity;
};

#endif // SHIPENTITY_H