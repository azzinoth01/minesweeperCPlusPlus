#pragma once
#include "Vector3.h"
#include <vector>
#include "D3D11Vertex.h"
#include "D3D11Buffer.h"
#include "D3D11Material.h"
#include "D3D11SampleState.h"
#include "IRender.h"
#include "Component.h"

class SpriteRenderer : public Component, public IRender {


public:
    SpriteRenderer();
    ~SpriteRenderer();

    



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

    // Inherited via Component
    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Start() override;
    virtual void Update() override;
    virtual void OnDestroy() override;
    virtual ComponentType GetType() override;

    // Inherited via IRender
    virtual void Init() override;
    virtual void BeginRender() override;
    virtual void Render() override;
    virtual void EndRender() override;
};

