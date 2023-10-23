#pragma once
#include "Vector3.h"
#include <vector>
#include "D3D11Vertex.h"
#include "D3D11Buffer.h"
#include "D3D11Material.h"
#include "D3D11SampleState.h"

class SpriteRenderer {


public:
    SpriteRenderer();
    ~SpriteRenderer();

    void InitRender();
    bool PreRender();
    bool Render();

    void SetMaterial(std::string& id);
    void SetMaterial(const std::string& vertexShaderFile, const std::string& pixelShaderFile);
    void SetTexture(std::string& id);
    void SetTexture(const std::string& textureFile);
    std::string GetMaterialID();
    std::string GetTextureID();

    void SetPosition(const Vector3& position);
    void SetWidth(float width);
    void SetHeight(float height);

    Vector3 GetPosition();
    float GetWidth();
    float GetHeight();

private:
    void CreateVertices();
    Vector3 _position;
    float _width;
    float _height;
    std::vector<VertexColoredTexture> _vertices;
    D3D11Buffer _vertexBuffer;
    D3D11SampleState _sampleState;
    std::string _materialID;
    std::string _textureID;
    bool _isChanged;
    bool _isInit;
};

