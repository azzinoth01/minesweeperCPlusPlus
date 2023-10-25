#pragma once
#include "Component.h"
#include <map> 
#include "ComponentType.h"
#include <memory>

class Entity {

public:
    Entity();
    ~Entity();

    void OnEnable();
    void OnDisable();
    void Start();
    void Update();
    void SetActive(bool active);
    bool GetActive();
    void OnDestroy();

    void Destroy();
    template<class T>
    void AddComponent() {
        std::shared_ptr pointer = std::make_shared<T>();
        _entityComponents[pointer.GetType()] = pointer;
    }
    void RemoveComponent(ComponentType type);
    template<class T>
    std::weak_ptr<T> GetComponent(ComponentType type) {
        if (_entityComponents.find(type) == _entityComponents.end()) {
            return std::weak_ptr<T>();
        }
        return std::static_pointer_cast<T> _entityComponents[type];
    }


private:
    int _id;
    bool _isActive;
    std::map<ComponentType,std::shared_ptr<Component>> _entityComponents;
};

