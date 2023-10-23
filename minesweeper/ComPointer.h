#pragma once
#include "Utility.h"


template<class T>
class ComPointer {
public:
    ComPointer() :_pointer(nullptr) {
    }


    ComPointer(const ComPointer<T>& base) :_pointer(nullptr) {
        Set(base);
    }
    ComPointer(T* pointer) :_pointer(nullptr) {
        Set(pointer);
    }
    ~ComPointer() {
        Set(nullptr);
    }

    ComPointer<T>& operator=(T* base) {
        Set(base);
        return *this;
    }

    ComPointer<T>& operator=(const ComPointer<T>& base) {
        if (*this != base) {
            Set(base);
        }
        return *this;
    }

    operator T* () {
        return _pointer;
    }
    operator T* () const {
        return _pointer;
    }
    T* operator->() {
        return _pointer;
    }
    const T* operator->() const {
        return _pointer;
    }


    inline T** GetPointerAddress() {
        return &_pointer;
    }
    void Reset() {
        *this = nullptr;
    }


private:
    T* _pointer;

    REMOVE_MOVE(ComPointer);



    void Set(T* pointer) {
        if (pointer != nullptr) {
            pointer->AddRef();
        }
        if (_pointer) {
            _pointer->Release();
            _pointer = nullptr;
        }
        _pointer = pointer;
    }
};


