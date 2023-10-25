#pragma once
#include "ComponentType.h"
#include <memory>
#include "Entity.h"

 class Component {

public:

    Component(Entity);
    virtual ~Component() {}
    virtual void OnEnable() = 0;
    virtual void OnDisable()=0;
    virtual void Start()=0;
    virtual void Update()=0;  
    void SetActive(bool active);
    bool GetActive();
    virtual void OnDestroy()=0;
    virtual ComponentType GetType()= 0;
    std::weak_ptr<Component> GetPointer();

 private:
    bool _isActive;
    int _entityID;
  

};

