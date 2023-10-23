#include "D3D11Renderer.h"
#include "D3D11Device.h"
#include "Color.h"




struct PerFrameConstantBufferData {
    float screenSize[2];
    float unused[2];
} _perFrameConstantBufferData;

D3D11Renderer::D3D11Renderer() {
}

D3D11Renderer::~D3D11Renderer() {
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

    return true;
}

bool D3D11Renderer::EndRender() {
    return D3D11Device::GetInstance()->Present(0);
}
