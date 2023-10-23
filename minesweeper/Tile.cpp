#include "Tile.h"

Tile::Tile(Vector2Int position) : _position(position), _value(0), _hasMine(false), _showState(0), _canBeClicked(true) {

    _spriteRender.InitRender();
    _spriteRender.SetMaterial("VertexShader.cso", "PixelShader.cso");
    SetRenderSprite();
}

Tile::~Tile() {
}

Vector2Int Tile::GetPosition() {
    return _position;
}

void Tile::SetPosition(Vector2Int position) {
    _position = position;
}

int Tile::GetValue() {
    return _value;
}

void Tile::SetValue(int value) {
    _value = value;
}

bool Tile::HasMine() {
    return _hasMine;
}

void Tile::SetMine(bool mine) {
    _hasMine = mine;
}

void Tile::IncreaseValueByOne() {
    _value = _value + 1;
    SetRenderSprite();
}

void Tile::ShowMine() {
    _showState = 3;
    SetRenderSprite();
    _canBeClicked = false;
}

void Tile::ShowMineClear() {
    _showState = 4;
    SetRenderSprite();
    _canBeClicked = false;
}

void Tile::ShowFlag() {
    _showState = 1;
    SetRenderSprite();
}

void Tile::ShowClosed() {
    _showState = 0;
    SetRenderSprite();
}

void Tile::ShowValue() {
    _showState = 2;
    SetRenderSprite();
    _canBeClicked = false;
}

void Tile::Reset() {
    _value = 0;
    _hasMine = false;
    _showState = 0;
    _canBeClicked = true;
    SetRenderSprite();
}

bool Tile::CanBeClicked() {
    return _canBeClicked;
}

void Tile::DisableClick() {
    _canBeClicked = false;
}

void Tile::ToogleFlagState() {
    if (_showState < 2) {
        _showState = (_showState + 1) % 2;
    }
    SetRenderSprite();
}

void Tile::SetRenderPosition(Vector3 pos) {
    _spriteRender.SetPosition(pos);
}

void Tile::SetRenderSize(Vector2Int size) {
    _spriteRender.SetWidth(size.X);
    _spriteRender.SetHeight(size.Y);

}

void Tile::PreRender() {
    _spriteRender.PreRender();
}

void Tile::Render() {
    _spriteRender.Render();
}

void Tile::SetRenderSprite() {
    if (_showState == 0) {
        _spriteRender.SetTexture("Assets\\TileClosed.png");
    }
    else if (_showState == 1) {
        _spriteRender.SetTexture("Assets\\TileFlag.png");
    }
    else if (_showState == 2) {
        _spriteRender.SetTexture("Assets\\Tile" + std::to_string(_value) + ".png");
    }
    else if (_showState == 3) {
        _spriteRender.SetTexture("Assets\\TileMine.png");
    }
    else if (_showState == 4) {
        _spriteRender.SetTexture("Assets\\TileMineFinish.png");
    }

}
