#pragma once
#include <memory>
#include "Entity.h"
#include <map>

class EntityContainer {

public:
    static EntityContainer* GetInstance();
    void AddEntity(Entity* entity);
    void RemoveEnity(int key);


private:
    EntityContainer();
    ~EntityContainer();
    static EntityContainer* _instance;

    std::map<int, std::shared_ptr<Entity>> _entityMap;
    int _counter;
};

