#pragma once
#include <d3d11.h>
#include "Utility.h"
#include "ComPointer.h"


class D3D11Buffer {

public:
    D3D11Buffer();
    ~D3D11Buffer();

    bool CreateStatic(void* data, size_t sizeInBytes, unsigned int bindFlags);
    bool CreateDynamic(size_t sizeInBytes, unsigned int bindFlags);
    void Release();
    bool Write(void* data);
    bool Write(void* data, size_t size);
    bool IsInit() const;
    size_t GetSize() const;
    ID3D11Buffer* GetBuffer();
    operator ID3D11Buffer* ();
    operator const  ID3D11Buffer* ();

private:
    REMOVE_COPY_MOVE(D3D11Buffer);

    bool _isInit;
    bool _isDynamic;
    size_t _size;
    ComPointer<ID3D11Buffer> _buffer;

};

