#pragma once
#include <d3d11.h>
#include "D3D11Pixelshader.h"
#include "D3D11Vertexshader.h"
#include "D3D11Buffer.h"
#include "ComPointer.h"
#include "Utility.h"
#include "SpriteRenderer.h"


class D3D11Renderer {

public:
    D3D11Renderer();
    ~D3D11Renderer();

    bool Init(HWND hwnd, int width, int height);
    void OnSizeChange(int width, int height);

    bool BeginRender();
    bool Render();
    bool EndRender();

private:
    REMOVE_COPY_MOVE(D3D11Renderer);

    D3D11Buffer _perFrameConstantBuffer;

    SpriteRenderer spriteRender;

};

