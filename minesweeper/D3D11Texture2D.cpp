#include "D3D11Texture2D.h"
#include "D3D11Device.h"
#include <WICTextureLoader.h>

D3D11_TEXTURE2D_DESC CreateTextureDescription(int width, int height, DXGI_FORMAT format, unsigned int bindFlags) {

    D3D11_TEXTURE2D_DESC textureDescription = {};
    textureDescription.Usage = D3D11_USAGE_DEFAULT;
    textureDescription.Format = format;
    textureDescription.Width = width;
    textureDescription.Height = height;
    textureDescription.MipLevels = 1;
    textureDescription.ArraySize = 1;
    textureDescription.SampleDesc.Count = 1;
    textureDescription.BindFlags = bindFlags;
    textureDescription.CPUAccessFlags = 0;

    return textureDescription;
}

D3D11Texture2D::D3D11Texture2D() : _isInit(false), _width(0), _height(0), _format(DXGI_FORMAT_UNKNOWN), _bindFlags(0) {
}

D3D11Texture2D::~D3D11Texture2D() {
    Release();
}

void D3D11Texture2D::Release() {
    _isInit = false;
    _srv.Reset();
    _rtv.Reset();
    _dsv.Reset();
    _texture.Reset();
}

bool D3D11Texture2D::Create(int width, int height, DXGI_FORMAT format, unsigned int bindFlags) {

    if (_isInit) {
        return false;
    }

    D3D11_TEXTURE2D_DESC textureDesc = CreateTextureDescription(width, height, format, bindFlags);


    if (Failed(D3D11Device::GetDevice()->CreateTexture2D(&textureDesc, nullptr, _texture.GetPointerAddress()))) {
        return false;
    }
    if (!CreateViews(bindFlags)) {
        return false;
    }

    _width = width;
    _height = height;
    _format = format;
    _bindFlags = bindFlags;
    _isInit = true;

    return true;
}



bool D3D11Texture2D::CreateFromFile(const std::string& file) {

    if (_isInit) {
        return false;
    }
    ComPointer<ID3D11Resource> resource;

    const std::wstring wFile = std::wstring(file.begin(), file.end());

    if (Failed(DirectX::CreateWICTextureFromFile(D3D11Device::GetDevice(), D3D11Device::GetContext(), wFile.c_str(), resource.GetPointerAddress(), _srv.GetPointerAddress()))) {
        return false;
    }
    if (Failed(resource->QueryInterface(IID_ID3D11Texture2D, reinterpret_cast<void**>(_texture.GetPointerAddress())))) {
        return false;
    }

    D3D11_TEXTURE2D_DESC textureDescription = {};
    _texture->GetDesc(&textureDescription);
    _width = textureDescription.Width;
    _height = textureDescription.Height;
    _format = textureDescription.Format;
    _bindFlags = D3D11_BIND_SHADER_RESOURCE;
    _isInit = true;

    return true;
}

bool D3D11Texture2D::CreateFromExisting(ID3D11Texture2D* texture, unsigned int bindFlags) {

    if (texture == nullptr || _isInit) {
        return false;
    }

    *_texture.GetPointerAddress() = texture;

    if (!CreateViews(bindFlags)) {
        return false;
    }

    D3D11_TEXTURE2D_DESC textureDescription = {};
    _texture->GetDesc(&textureDescription);
    _width = textureDescription.Width;
    _height = textureDescription.Height;
    _format = textureDescription.Format;
    _bindFlags = bindFlags;
    _isInit = true;

    return false;
}

ID3D11RenderTargetView* D3D11Texture2D::GetRTV() {
    return _rtv;
}

ID3D11ShaderResourceView* D3D11Texture2D::GetSRV() {
    return _srv;
}

ID3D11DepthStencilView* D3D11Texture2D::GetDSV() {
    return _dsv;
}

unsigned int D3D11Texture2D::GetBindFlags() const {
    return _bindFlags;
}

bool D3D11Texture2D::IsInit() const {
    return _isInit;
}

DXGI_FORMAT D3D11Texture2D::GetFormat() const {
    return _format;
}

void D3D11Texture2D::SetupForRendering(unsigned int slot) {
    ID3D11DeviceContext* contex = D3D11Device::GetContext();
    contex->VSSetShaderResources(slot, 1, _srv.GetPointerAddress());
    contex->PSSetShaderResources(slot, 1, _srv.GetPointerAddress());
}

bool D3D11Texture2D::CreateViews(unsigned int bindFlags) {


    if (IsFlagSet(D3D11_BIND_RENDER_TARGET, bindFlags)) {
        if (Failed(D3D11Device::GetDevice()->CreateRenderTargetView(_texture, nullptr, _rtv.GetPointerAddress()))) {
            return false;
        }
    }
    if (IsFlagSet(D3D11_BIND_SHADER_RESOURCE, bindFlags)) {
        if (Failed(D3D11Device::GetDevice()->CreateShaderResourceView(_texture, nullptr, _srv.GetPointerAddress()))) {
            return false;
        }
    }
    if (IsFlagSet(D3D11_BIND_DEPTH_STENCIL, bindFlags)) {
        if (Failed(D3D11Device::GetDevice()->CreateDepthStencilView(_texture, nullptr, _dsv.GetPointerAddress()))) {
            return false;
        }
    }


    return true;
}
