#include "D3D11Vertexshader.h"
#include "D3D11Device.h"
#include <d3dcompiler.h> 


D3D11VertexShader::D3D11VertexShader() : _isInit(false) {
}

D3D11VertexShader::~D3D11VertexShader() {
}

void D3D11VertexShader::Release() {
    if (_isInit) {
        _vertexShader = nullptr;
        _inputLayer = nullptr;
        _isInit = false;
    }
}

bool D3D11VertexShader::CreateVertexShader(const std::string& file, const VertexDescription& vertexDescription) {

    ComPointer<ID3DBlob> vsBlob;
    const std::wstring wFile = std::wstring(file.begin(), file.end());
    if (Failed(D3DReadFileToBlob(wFile.c_str(), vsBlob.GetPointerAddress()))) {
        return false;
    }

    if (Failed(D3D11Device::GetDevice()->CreateInputLayout(vertexDescription.InputElementDesc, static_cast<UINT>(vertexDescription.NumberInputElements), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), _inputLayer.GetPointerAddress()))) {
        return false;
    }

    if (Failed(D3D11Device::GetDevice()->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, _vertexShader.GetPointerAddress()))) {
        return false;
    }
    _isInit = true;
    _vertexDescription = vertexDescription;

    return true;
}


void D3D11VertexShader::SetupForRendering() {
    ID3D11DeviceContext* context = D3D11Device::GetContext();
    context->VSSetShader(_vertexShader, nullptr, 0);
    context->IASetInputLayout(_inputLayer);

}
