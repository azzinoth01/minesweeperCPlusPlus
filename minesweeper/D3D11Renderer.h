#pragma once
#include <d3d11.h>
#include "D3D11Pixelshader.h"
#include "D3D11Vertexshader.h"
#include "D3D11Buffer.h"
#include "ComPointer.h"
#include "Utility.h"
#include "SpriteRenderer.h"
#include "IRender.h"
#include <memory>

class D3D11Renderer {

public:
    

    static D3D11Renderer* GetInstance();

    bool Init(HWND hwnd, int width, int height);
    void OnSizeChange(int width, int height);

    bool BeginRender();
    bool Render();
    bool EndRender();

    void AddRenderObject(std::weak_ptr<IRender> renderObject);

private:
    REMOVE_COPY_MOVE(D3D11Renderer);

    D3D11Renderer();
    ~D3D11Renderer();

    static D3D11Renderer* _instance;

    D3D11Buffer _perFrameConstantBuffer;
    std::vector<std::weak_ptr<IRender>> _renderList;
    
};

