#include "D3D11Vertex.h"
#include <d3d11.h>
#include "Utility.h"

D3D11_INPUT_ELEMENT_DESC VertexColoredTextureInputElementDescription[] = {
    {
        "POSITION",
        0,
        DXGI_FORMAT_R32G32B32_FLOAT,
        0,
        D3D11_APPEND_ALIGNED_ELEMENT,
        D3D11_INPUT_PER_VERTEX_DATA,
        0
    },
    {
        "COLOR",
        0,
        DXGI_FORMAT_R32G32B32A32_FLOAT,
        0,
        D3D11_APPEND_ALIGNED_ELEMENT,
        D3D11_INPUT_PER_VERTEX_DATA,
        0
    },
    {
        "TEXCOORD",
        0,
        DXGI_FORMAT_R32G32_FLOAT,
        0,
        D3D11_APPEND_ALIGNED_ELEMENT,
        D3D11_INPUT_PER_VERTEX_DATA,
        0
    },
};

VertexDescription VertexColoredTexture::Description = {
    sizeof(VertexColoredTexture),
    ARRAY_COUNT(VertexColoredTextureInputElementDescription),
    VertexColoredTextureInputElementDescription

};