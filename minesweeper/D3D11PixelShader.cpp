#include "D3D11Pixelshader.h"
#include "D3D11Device.h"
#include <d3dcompiler.h> 
#include <string>


D3D11PixelShader::D3D11PixelShader() : _isInit(false) {
}

D3D11PixelShader::~D3D11PixelShader() {
}

void D3D11PixelShader::Release() {
    if (_isInit == true) {
        _pixelShader = nullptr;
        _isInit = false;
    }


}

void D3D11PixelShader::SetupForRendering() {
    D3D11Device::GetContext()->PSSetShader(_pixelShader, nullptr, 0);
}

bool D3D11PixelShader::IsInit() const {
    return _isInit;
}

bool D3D11PixelShader::CreatePixelShader(const std::string& file) {


    ComPointer<ID3DBlob> psBlob = nullptr;
    const std::wstring wFile = std::wstring(file.begin(), file.end());
    if (Failed(D3DReadFileToBlob(wFile.c_str(), psBlob.GetPointerAddress()))) {
        return false;
    }


    if (Failed(D3D11Device::GetDevice()->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, _pixelShader.GetPointerAddress()))) {
        return false;
    }
    _isInit = true;

    return true;
}
