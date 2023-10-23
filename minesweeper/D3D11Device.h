#pragma once
#include <d3d11.h>
#include "ComPointer.h"
#include "Utility.h"
#include "Color.h"
#include "D3D11Texture2D.h"
#include <map>
#include "D3D11Material.h"

class D3D11Device {


public:
    static D3D11Device* GetInstance();
    static ID3D11Device* GetDevice();
    ID3D11Device* GetDev();
    static ID3D11DeviceContext* GetContext();
    ID3D11DeviceContext* GetImmediateContext();

    static void DestroyInstance();
    bool Create(HWND hwnd, int width, int height);
    void ResizeSwapchain(int width, int height);
    void ClearBackBuffer(const Color& color);
    void Clear(ID3D11RenderTargetView* rtv, const Color& color);
    void ClearDSV(uint32_t clearFlags, float depth, uint8_t stencil);
    bool Present(unsigned int syncInterval);
    void SetRenderTargets(unsigned int numberViews, ID3D11RenderTargetView* rtv, bool setDSV);
    void ResetRenderTargets();
    int GetScreenWidth();
    int GetScreenHeight();

    D3D11Material* GetMaterial(std::string id);
    D3D11Texture2D* GetTexture(std::string id);
    void AddMaterial(const std::string& vertexShaderFile, const std::string& pixelShaderFile);
    void AddTexture(const std::string& textureFile);


private:
    REMOVE_COPY_MOVE(D3D11Device);

    D3D11Device();
    ~D3D11Device();

    bool CreateBackBuffer();
    bool CreateDepthBuffer();

    void SetViewPort(int width, int height);


    static D3D11Device* _instance;

    D3D11Texture2D _backBuffer;
    D3D11Texture2D _depthBuffer;

    ComPointer<ID3D11RenderTargetView> _renderTargetView;
    ComPointer<ID3D11Device> _device;
    ComPointer<ID3D11DeviceContext> _immediateContext;
    ComPointer<IDXGISwapChain> _swapChain;

    std::map<std::string, D3D11Material> _materialMap;
    std::map<std::string, D3D11Texture2D> _textureMap;

    int _width;
    int _height;

};

