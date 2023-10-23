#pragma once


struct D3D11_INPUT_ELEMENT_DESC;

struct VertexDescription {
    size_t VertexSize;
    size_t NumberInputElements;
    D3D11_INPUT_ELEMENT_DESC* InputElementDesc;
};

struct VertexColoredTexture {
    float Positons[3];
    float color[4];
    float UV[2];

    static VertexDescription Description;
};

