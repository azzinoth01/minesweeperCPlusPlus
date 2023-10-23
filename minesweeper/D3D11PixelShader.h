#pragma once

#include <d3d11.h>
#include "ComPointer.h"
#include "Utility.h"

class D3D11PixelShader {

public:
    D3D11PixelShader();
    ~D3D11PixelShader();

    void Release();
    void SetupForRendering();
    bool IsInit() const;
    bool CreatePixelShader(const std::string& file);

private:
    REMOVE_COPY_MOVE(D3D11PixelShader);

    bool _isInit;
    ComPointer<ID3D11PixelShader>_pixelShader;

};

