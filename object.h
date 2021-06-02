#pragma once
#include <string>

class GameObject
{
    virtual const std::string & getName() const = 0;
    virtual void update() = 0;
};

class InventoryObject : public GameObject
{

};
