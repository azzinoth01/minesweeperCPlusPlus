#include "SpriteRenderer.h"
#include "D3D11Device.h"




SpriteRenderer::SpriteRenderer() : _position(Vector3(100, 100, 0)), _width(600), _height(600), _isChanged(false), _isInit(false) {

    CreateVertices();

}

SpriteRenderer::~SpriteRenderer() {
}

void SpriteRenderer::InitRender() {


    if (!_vertexBuffer.CreateStatic(_vertices.data(), _vertices.size() * sizeof(VertexColoredTexture), D3D11_BIND_VERTEX_BUFFER)) {
        _isInit = false;
    }

    _sampleState.Init(D3D11SampleState::ANISOTROPIC_FILTER, D3D11_TEXTURE_ADDRESS_CLAMP, D3D11_COMPARISON_ALWAYS, 4, 0, D3D11_FLOAT32_MAX, 0);

    _isInit = true;
}

bool SpriteRenderer::PreRender() {
    if (_isInit == false) {
        return false;
    }
    if (_isChanged) {
        _vertices.clear();
        CreateVertices();
        _vertexBuffer.Release();
        if (!_vertexBuffer.CreateStatic(_vertices.data(), _vertices.size() * sizeof(VertexColoredTexture), D3D11_BIND_VERTEX_BUFFER)) {
            return false;
        }
        _isChanged = false;
    }



    return true;
}

bool SpriteRenderer::Render() {
    if (_isInit == false) {
        return false;
    }
    ID3D11DeviceContext* contex = D3D11Device::GetContext();


    D3D11Material* mat = D3D11Device::GetInstance()->GetMaterial(_materialID);
    if (mat != nullptr) {
        mat->SetupForRendering();
    }
    const UINT stride = sizeof(VertexColoredTexture);
    constexpr UINT offset = 0;
    ID3D11Buffer* vertexBuffer = _vertexBuffer.GetBuffer();
    contex->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    contex->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

    D3D11Texture2D* texture = D3D11Device::GetInstance()->GetTexture(_textureID);
    if (texture != nullptr) {
        texture->SetupForRendering(0);
        _sampleState.SetupForRendering(0);
    }

    contex->Draw(_vertices.size(), 0);

    return false;
}

void SpriteRenderer::SetMaterial(std::string& id) {
    _materialID = id;
}

void SpriteRenderer::SetMaterial(const std::string& vertexShaderFile, const std::string& pixelShaderFile) {
    _materialID = vertexShaderFile + pixelShaderFile;
    D3D11Device::GetInstance()->AddMaterial(vertexShaderFile, pixelShaderFile);
}

void SpriteRenderer::SetTexture(std::string& id) {
    _textureID = id;
}

void SpriteRenderer::SetTexture(const std::string& textureFile) {
    _textureID = textureFile;
    D3D11Device::GetInstance()->AddTexture(textureFile);
}

std::string SpriteRenderer::GetMaterialID() {
    return _materialID;
}

std::string SpriteRenderer::GetTextureID() {
    return _textureID;
}

void SpriteRenderer::SetPosition(const Vector3& position) {
    _position = position;
    _isChanged = true;
}

void SpriteRenderer::SetWidth(float width) {
    _width = width;
    _isChanged = true;
}

void SpriteRenderer::SetHeight(float height) {
    _height = height;
    _isChanged = true;
}

Vector3 SpriteRenderer::GetPosition() {
    return _position;
}

float SpriteRenderer::GetWidth() {
    return _width;
}

float SpriteRenderer::GetHeight() {
    return _height;
}

void SpriteRenderer::CreateVertices() {
    Vector3 botRight = _position + Vector3::VectorRight * _width;
    Vector3 botLeft = _position;
    Vector3 topRight = _position + Vector3::VectorRight * _width + Vector3::VectorUp * _height;
    Vector3 topLeft = _position + Vector3::VectorUp * _height;

    Color white = Color::White;
    _vertices.push_back({ botRight.X, botRight.Y, botRight.Z, white.GetR(), white.GetG(), white.GetB(), white.GetA(), 1, 1 });
    _vertices.push_back({ botLeft.X , botLeft.Y , botLeft.Z , white.GetR(), white.GetG(), white.GetB(), white.GetA(), 0, 1 });
    _vertices.push_back({ topRight.X, topRight.Y, topRight.Z, white.GetR(), white.GetG(), white.GetB(), white.GetA(), 1, 0 });
    _vertices.push_back({ topLeft.X , topLeft.Y , topLeft.Z , white.GetR(), white.GetG(), white.GetB(), white.GetA(), 0, 0 });
}
