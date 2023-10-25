#include "D3D11Renderer.h"
#include "D3D11Device.h"
#include "Color.h"

struct PerFrameConstantBufferData {
    float screenSize[2];
    float unused[2];
} _perFrameConstantBufferData;

D3D11Renderer* D3D11Renderer::_instance = nullptr;

D3D11Renderer::D3D11Renderer() {
}

D3D11Renderer::~D3D11Renderer() {
}

D3D11Renderer* D3D11Renderer::GetInstance() {
    if (_instance == nullptr) {
        _instance = new D3D11Renderer();
    }
    return _instance;
}

bool D3D11Renderer::Init(HWND hwnd, int width, int height) {
    if (!D3D11Device::GetInstance()->Create(hwnd, width, height)) {
        return false;
    }

    if (!_perFrameConstantBuffer.CreateDynamic(sizeof(_perFrameConstantBufferData), D3D11_BIND_CONSTANT_BUFFER)) {
        return false;
    }

    _perFrameConstantBufferData.screenSize[0] = width;
    _perFrameConstantBufferData.screenSize[1] = height;


    return true;
}

void D3D11Renderer::OnSizeChange(int width, int height) {

    D3D11Device::GetInstance()->ResizeSwapchain(width, height);
}



bool D3D11Renderer::BeginRender() {
    D3D11Device::GetInstance()->ClearBackBuffer(Color::White);
    D3D11Device::GetInstance()->ResetRenderTargets();
    D3D11Device::GetInstance()->ClearDSV(D3D11_CLEAR_DEPTH, 1.0f, 0);

    auto it = _renderList.begin();
    while (it != _renderList.end()) {
      auto render=  it->lock();
        if (render) {
            render->BeginRender();
            it++;
        }
        else {
           it= _renderList.erase(it);
        }
    }
    return true;
}

bool D3D11Renderer::Render() {

    ID3D11DeviceContext* contex = D3D11Device::GetContext();
    D3D11Device* device = D3D11Device::GetInstance();

    _perFrameConstantBufferData.screenSize[0] = device->GetScreenWidth();
    _perFrameConstantBufferData.screenSize[1] = device->GetScreenHeight();
    ID3D11Buffer* perFrameConstantBuffer = _perFrameConstantBuffer.GetBuffer();
    contex->VSSetConstantBuffers(0, 1, &perFrameConstantBuffer);
    contex->PSSetConstantBuffers(0, 1, &perFrameConstantBuffer);
    if (!_perFrameConstantBuffer.Write(&_perFrameConstantBufferData, sizeof(_perFrameConstantBufferData))) {
        return false;
    }

    auto it = _renderList.begin();
    while (it != _renderList.end()) {
        auto render = it->lock();
        if (render) {
            render->Render();
            it++;
        }
        else {
            it = _renderList.erase(it);
        }
    }
    return true;
}

bool D3D11Renderer::EndRender() {
    auto it = _renderList.begin();
    while (it != _renderList.end()) {
        auto render = it->lock();
        if (render) {
            render->EndRender();
            it++;
        }
        else {
            it = _renderList.erase(it);
        }
    }
    return D3D11Device::GetInstance()->Present(0);
}

void D3D11Renderer::AddRenderObject(std::weak_ptr<IRender> renderObject) {
    _renderList.push_back(renderObject);
}
