#include "D3D11Material.h"
#include "D3D11Device.h"


D3D11Material::D3D11Material() {
}

D3D11Material::~D3D11Material() {
}

bool D3D11Material::Create(const std::string& vertexShaderFile, const std::string& pixelShaderFile) {
    if (!_vertexShader.CreateVertexShader(vertexShaderFile, VertexColoredTexture::Description)) {
        return false;
    }
    if (!_pixelShader.CreatePixelShader(pixelShaderFile)) {
        return false;
    }
    return true;
}

bool D3D11Material::SetVertexShader(const std::string& file) {
    if (!_vertexShader.CreateVertexShader(file, VertexColoredTexture::Description)) {
        return false;
    }
    return true;
}

bool D3D11Material::SetPixelShader(const std::string& file) {
    if (!_pixelShader.CreatePixelShader(file)) {
        return false;
    }
    return true;
}

void D3D11Material::SetupForRendering() {
    _vertexShader.SetupForRendering();
    _pixelShader.SetupForRendering();


}
