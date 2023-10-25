#include "Component.h"

Component::Component(): _isActive(false) {
}

void Component::SetActive(bool active) {
    if (active && active != _isActive) {
        _isActive = active;
        OnEnable();
    }
    else if (active == false && active != _isActive) {
        _isActive = active;
        OnDisable();
    }
}

bool Component::GetActive() {
    return _isActive;
}

std::weak_ptr<Component> Component::GetPointer() {
    return std::weak_ptr<Component>();
}
