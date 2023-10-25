#include "Entity.h"

Entity::Entity():_id(-1),_isActive(false) {
}

Entity::~Entity() {
}

void Entity::OnEnable() {
    for (auto pair : _entityComponents) {
        pair.second->OnEnable();
    }
}

void Entity::OnDisable() {
    for (auto pair : _entityComponents) {
        pair.second->OnDisable();
    }
}

void Entity::Start() {
    for (auto pair : _entityComponents) {
        pair.second->Start();
    }
}

void Entity::Update() {
    for (auto pair : _entityComponents) {
        pair.second->Update();
    }
}

void Entity::SetActive(bool active) {
    
    if (active && active != _isActive) {
        _isActive = active;
        OnEnable();
    }
    else if(active== false && active != _isActive  ) {
        _isActive = active;
        OnDisable();
    }
}

bool Entity::GetActive() {
    return _isActive;
}

void Entity::OnDestroy() {

    for (auto pair : _entityComponents) {
        pair.second->OnDestroy();
    }
}

void Entity::Destroy() {
    OnDestroy();
}

void Entity::RemoveComponent(ComponentType type) {
    
    auto it =_entityComponents.find(type);

    if (it != _entityComponents.end()) {
        _entityComponents.erase(it);
    }
}


