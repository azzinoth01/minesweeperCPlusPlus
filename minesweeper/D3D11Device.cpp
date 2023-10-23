#include "D3D11Device.h"
#include <d3d11.h>  

D3D11Device* D3D11Device::_instance = nullptr;

D3D11Device* D3D11Device::GetInstance() {

    if (_instance == nullptr) {
        _instance = new D3D11Device();
    }

    return _instance;
}

ID3D11Device* D3D11Device::GetDevice() {
    if (_instance == nullptr) {
        return nullptr;
    }
    return _instance->_device;
}

ID3D11Device* D3D11Device::GetDev() {
    return _device;
}

ID3D11DeviceContext* D3D11Device::GetContext() {
    if (_instance == nullptr) {
        return nullptr;
    }
    return _instance->_immediateContext;
}

ID3D11DeviceContext* D3D11Device::GetImmediateContext() {
    return _immediateContext;
}

void D3D11Device::DestroyInstance() {
    delete _instance;
    _instance = nullptr;
}

bool D3D11Device::Create(HWND hwnd, int width, int height) {

    _width = width;
    _height = height;

    DXGI_SWAP_CHAIN_DESC desc = {};
    desc.BufferCount = 1;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferDesc.Width = _width;
    desc.BufferDesc.Height = _height;
    desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.OutputWindow = hwnd;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    desc.Windowed = TRUE;


    if (Failed(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, D3D11_SDK_VERSION, &desc, _swapChain.GetPointerAddress(), _device.GetPointerAddress(), nullptr, _immediateContext.GetPointerAddress()))) {
        return false;
    }

    if (!CreateBackBuffer()) {
        return false;
    }
    if (!CreateDepthBuffer()) {
        return false;
    }

    SetViewPort(_width, _height);




    return true;
}

void D3D11Device::ResizeSwapchain(int width, int height) {

    _width = width;
    _height = height;

    _backBuffer.Release();
    _depthBuffer.Release();

    if (Failed(_swapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0))) {
        return;
    }
    CreateBackBuffer();
    CreateDepthBuffer();

    SetViewPort(width, height);
}

void D3D11Device::ClearBackBuffer(const Color& color) {
    Clear(_backBuffer.GetRTV(), color);
}

void D3D11Device::Clear(ID3D11RenderTargetView* rtv, const Color& color) {
    _immediateContext->ClearRenderTargetView(rtv, color.ColorValue);
}
void D3D11Device::ClearDSV(uint32_t clearFlags, float depth, uint8_t stencil) {
    _immediateContext->ClearDepthStencilView(_depthBuffer.GetDSV(), clearFlags, depth, stencil);
}
bool D3D11Device::Present(unsigned int syncInterval) {
    return !Failed(_swapChain->Present(syncInterval, 0));

}
void D3D11Device::SetRenderTargets(unsigned int numberViews, ID3D11RenderTargetView* rtv, bool setDSV) {

    if (setDSV) {
        _immediateContext->OMSetRenderTargets(numberViews, &rtv, _depthBuffer.GetDSV());
    }
    else {
        _immediateContext->OMSetRenderTargets(numberViews, &rtv, nullptr);
    }
}
void D3D11Device::ResetRenderTargets() {

    ID3D11RenderTargetView* rtv = _backBuffer.GetRTV();
    _immediateContext->OMSetRenderTargets(1, &rtv, _depthBuffer.GetDSV());

}

int D3D11Device::GetScreenWidth() {
    return _width;
}

int D3D11Device::GetScreenHeight() {
    return _height;
}

D3D11Material* D3D11Device::GetMaterial(std::string id) {

    if (_materialMap.end() == _materialMap.find(id)) {
        return nullptr;
    }

    return &_materialMap[id];
}

D3D11Texture2D* D3D11Device::GetTexture(std::string id) {
    if (_textureMap.end() == _textureMap.find(id)) {
        return nullptr;
    }

    return &_textureMap[id];
}

void D3D11Device::AddMaterial(const std::string& vertexShaderFile, const std::string& pixelShaderFile) {



    D3D11Material& mat = _materialMap[vertexShaderFile + pixelShaderFile];
    mat.Create(vertexShaderFile, pixelShaderFile);


}

void D3D11Device::AddTexture(const std::string& textureFile) {

    D3D11Texture2D& texture = _textureMap[textureFile];
    texture.CreateFromFile(textureFile);


}


bool D3D11Device::CreateBackBuffer() {
    ID3D11Texture2D* buffer = nullptr;
    if (Failed(_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&buffer)))) {
        return false;
    }
    if (_backBuffer.CreateFromExisting(buffer, D3D11_BIND_RENDER_TARGET)) {
        return false;
    }

    return true;
}

bool D3D11Device::CreateDepthBuffer() {

    if (!_depthBuffer.Create(_width, _height, DXGI_FORMAT_D32_FLOAT, D3D11_BIND_DEPTH_STENCIL)) {
        return false;
    }

    return true;
}

void D3D11Device::SetViewPort(int width, int height) {
    D3D11_VIEWPORT viewPort;
    viewPort.Width = static_cast<float> (width);
    viewPort.Height = static_cast<float> (height);
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    _immediateContext->RSSetViewports(1, &viewPort);


}

D3D11Device::D3D11Device() : _width(0), _height(0) {
}

D3D11Device::~D3D11Device() {
}


