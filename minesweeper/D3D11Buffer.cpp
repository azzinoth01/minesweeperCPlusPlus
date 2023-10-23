#include "D3D11Buffer.h"
#include "D3D11Device.h"

D3D11Buffer::D3D11Buffer() :_isInit(false), _isDynamic(false), _size(false) {
}

D3D11Buffer::~D3D11Buffer() {
}

bool D3D11Buffer::CreateStatic(void* data, size_t sizeInBytes, unsigned int bindFlags) {

    if (_isInit) {
        return false;
    }

    ID3D11Device* device = D3D11Device::GetDevice();

    if (device == nullptr) {
        return false;
    }

    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = sizeInBytes;
    desc.BindFlags = bindFlags;

    D3D11_SUBRESOURCE_DATA subressourceData = {};
    subressourceData.pSysMem = data;

    if (Failed(device->CreateBuffer(&desc, &subressourceData, _buffer.GetPointerAddress()))) {
        return false;
    }

    _isInit = true;
    _size = sizeInBytes;
    _isDynamic = false;


    return true;
}

bool D3D11Buffer::CreateDynamic(size_t sizeInBytes, unsigned int bindFlags) {
    if (_isInit) {
        return false;
    }

    ID3D11Device* device = D3D11Device::GetDevice();

    if (device == nullptr) {
        return false;
    }

    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.ByteWidth = sizeInBytes;
    desc.BindFlags = bindFlags;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    if (Failed(device->CreateBuffer(&desc, nullptr, _buffer.GetPointerAddress()))) {
        return false;
    }

    _isInit = true;
    _size = sizeInBytes;
    _isDynamic = true;


    return true;
}

void D3D11Buffer::Release() {
    _buffer = nullptr;
    _isInit = false;
    _isDynamic = false;
    _size = 0;
}

bool D3D11Buffer::Write(void* data) {

    return Write(data, _size);
}

bool D3D11Buffer::Write(void* data, size_t size) {

    if (!_isDynamic) {
        return false;
    }
    if (_size < size) {
        return false;
    }

    ID3D11DeviceContext* context = D3D11Device::GetContext();

    if (context == nullptr) {
        return false;
    }

    D3D11_MAPPED_SUBRESOURCE mappedSubresource = {};

    if (Failed(context->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource))) {
        return false;
    }

    memcpy(mappedSubresource.pData, data, size);
    context->Unmap(_buffer, 0);

    return true;
}

bool D3D11Buffer::IsInit() const {
    return _isInit;
}

size_t D3D11Buffer::GetSize() const {
    return _size;
}

ID3D11Buffer* D3D11Buffer::GetBuffer() {
    return _buffer;
}

D3D11Buffer::operator ID3D11Buffer* () {
    return _buffer;
}


D3D11Buffer::operator const ID3D11Buffer* () {
    return _buffer;
}
