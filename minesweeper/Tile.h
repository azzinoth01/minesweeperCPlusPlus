#pragma once
#include "Vector2Int.h"
#include "SpriteRenderer.h"

class Tile {
public:
    Tile(Vector2Int positon);
    ~Tile();

    Vector2Int GetPosition();
    void SetPosition(Vector2Int position);
    int GetValue();
    void SetValue(int value);
    bool HasMine();
    void SetMine(bool mine);
    void IncreaseValueByOne();

    void ShowMine();
    void ShowMineClear();
    void ShowFlag();
    void ShowClosed();
    void ShowValue();
    void Reset();

    bool CanBeClicked();
    void DisableClick();
    void ToogleFlagState();

    void SetRenderPosition(Vector3 pos);
    void SetRenderSize(Vector2Int size);
    void PreRender();
    void Render();

private:
    Vector2Int _position;
    int _value;
    bool _hasMine;
    int _showState;
    bool _canBeClicked;
    SpriteRenderer _spriteRender;
    void SetRenderSprite();
};

