#pragma once
#include "ComPointer.h"
#include <d3d11.h>
#include "Color.h"
#include <string>

class D3D11Texture2D {

public:
    D3D11Texture2D();
    ~D3D11Texture2D();

    void Release();
    bool Create(int width, int height, DXGI_FORMAT format, unsigned int bindFlags);
    bool CreateFromFile(const std::string& file);
    bool CreateFromExisting(ID3D11Texture2D* texture, unsigned int bindFlags);

    ID3D11RenderTargetView* GetRTV();
    ID3D11ShaderResourceView* GetSRV();
    ID3D11DepthStencilView* GetDSV();

    void SetupForRendering(unsigned int slot);
    bool IsInit() const;
    DXGI_FORMAT GetFormat() const;
    unsigned int GetBindFlags() const;

private:
    REMOVE_COPY_MOVE(D3D11Texture2D);

    bool CreateViews(unsigned int bindFlags);

    bool _isInit;
    std::string _file;
    int _width;
    int _height;
    DXGI_FORMAT _format;
    unsigned int _bindFlags;
    ComPointer<ID3D11RenderTargetView> _rtv;
    ComPointer <ID3D11ShaderResourceView> _srv;
    ComPointer<ID3D11DepthStencilView> _dsv;
    ComPointer<ID3D11Texture2D> _texture;
};

