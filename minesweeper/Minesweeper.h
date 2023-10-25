#pragma once
#include <map>
#include "Tile.h"
#include "Vector2Int.h"

class Minesweeper {

public:
    Minesweeper();
    ~Minesweeper();

    void GenerateField(Vector2Int size);
    void GenerateMineField(int mines, Vector2Int excludePosition);
    Vector2Int GetSize();
    Tile* GetTile(Vector2Int position);

    void BeginRender();
    void Render();
    void Reset();

    void LeftClickOnPosition(Vector2Int position);
    void RightClickOnPosition(Vector2Int position);

private:
    std::map<Vector2Int, Tile*> _mineField;
    Vector2Int _size;
    bool _isInit;
    int _remainingFields;
    int _mines;
    void IncreaseValueSourroundingTiles(Vector2Int pos);
    void LeftClickSurroundingTiles(Vector2Int position);
    void LeftClickClickTile(Vector2Int position);
};

