#pragma once
#include "D3D11Vertex.h"
#include "ComPointer.h"
#include "Utility.h"

class D3D11VertexShader {

public:
    D3D11VertexShader();
    ~D3D11VertexShader();

    void Release();
    bool CreateVertexShader(const std::string& file, const VertexDescription& vertexDescription);
    void SetupForRendering();

private:
    REMOVE_COPY_MOVE(D3D11VertexShader);
    bool _isInit;
    ComPointer<ID3D11InputLayout> _inputLayer;
    ComPointer<ID3D11VertexShader> _vertexShader;
    VertexDescription _vertexDescription;
};

