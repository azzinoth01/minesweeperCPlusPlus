#include "D3D11SampleState.h"
#include "D3D11Device.h"

D3D11SampleState::D3D11SampleState() : _isInit(false) {
}

D3D11SampleState::~D3D11SampleState() {
}

void D3D11SampleState::Release() {
    _isInit = false;
    _sampleState = nullptr;
}

void D3D11SampleState::SetupForRendering(unsigned int slot) {
    ID3D11SamplerState* sample = _sampleState;
    D3D11Device::GetContext()->PSSetSamplers(slot, 1, &sample);
}

bool D3D11SampleState::Init(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE addressMode, D3D11_COMPARISON_FUNC compare, unsigned int maxAnistrop, float minLOD, float maxLOD, float mipLODBias) {

    if (_isInit) {
        return false;
    }

    D3D11_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter = filter;
    samplerDesc.AddressU = addressMode;
    samplerDesc.AddressV = addressMode;
    samplerDesc.AddressW = addressMode;
    samplerDesc.MaxAnisotropy = maxAnistrop;
    samplerDesc.ComparisonFunc = compare;
    samplerDesc.MinLOD = minLOD;
    samplerDesc.MaxLOD = maxLOD;
    samplerDesc.MipLODBias = mipLODBias;

    if (Failed(D3D11Device::GetDevice()->CreateSamplerState(&samplerDesc, _sampleState.GetPointerAddress())))
        return false;

    _isInit = true;

    return true;
}

bool D3D11SampleState::GetInit() {


    return _isInit;
}
