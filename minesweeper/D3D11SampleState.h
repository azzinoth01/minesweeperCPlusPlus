#pragma once
#include <d3d11.h>
#include "ComPointer.h"

class D3D11SampleState {

public:
    D3D11SampleState();
    ~D3D11SampleState();

    void Release();
    void SetupForRendering(unsigned int slot);
    bool Init(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE addressMode, D3D11_COMPARISON_FUNC compare, unsigned int maxAnistrop, float minLOD, float maxLOD, float mipLODBias);
    bool GetInit();

    static const D3D11_FILTER POINT_FILTER = D3D11_FILTER_MIN_MAG_MIP_POINT;
    static const D3D11_FILTER BILINEAR_FILTER = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
    static const D3D11_FILTER TRILINEAR_FILTER = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    static const D3D11_FILTER ANISOTROPIC_FILTER = D3D11_FILTER_ANISOTROPIC;

private:
    bool _isInit;
    ComPointer<ID3D11SamplerState> _sampleState;
};

