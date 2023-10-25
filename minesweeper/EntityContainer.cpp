#include "EntityContainer.h"

EntityContainer* EntityContainer::_instance = nullptr;

EntityContainer* EntityContainer::GetInstance() {
    if (_instance == nullptr) {
        _instance = new EntityContainer();
    }
    return _instance;
}

void EntityContainer::AddEntity(Entity* entity) {
    _counter = _counter + 1;
    _entityMap[_counter] = std::make_shared<Entity>(entity);
}



EntityContainer::EntityContainer() {
}

EntityContainer::~EntityContainer() {
}
