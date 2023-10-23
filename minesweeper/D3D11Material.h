#pragma once
#include <string>
#include "D3D11Pixelshader.h"
#include "D3D11Vertexshader.h"
#include "D3D11Buffer.h"


class D3D11Material {

public:
    D3D11Material();
    ~D3D11Material();

    bool Create(const std::string& vertexShaderFile, const std::string& pixelShaderFile);

    bool SetVertexShader(const std::string& file);
    bool SetPixelShader(const std::string& file);

    void SetupForRendering();


private:
    D3D11PixelShader _pixelShader;
    D3D11VertexShader _vertexShader;

};

