#include "Minesweeper.h"
#include <ctime>

Minesweeper::Minesweeper() : _isInit(false) {
}

Minesweeper::~Minesweeper() {
    for (auto& pair : _mineField) {
        delete pair.second;
    }
}

void Minesweeper::GenerateField(Vector2Int size) {
    _size = size;
    _remainingFields = _size.X * _size.Y;
    Vector3 offset(100, 0, 0);

    for (int a = 0; a < _size.X; a++) {
        for (int b = 0; b < _size.Y; b++) {

            Tile* tile = new Tile(Vector2Int(a, b));
            tile->SetRenderSize(Vector2Int(50, 50));
            Vector3 renderPositon = Vector3::VectorRight * a * 50 + Vector3::VectorUp * b * 50 + offset;
            tile->SetRenderPosition(renderPositon);
            _mineField[Vector2Int(a, b)] = tile;
        }
    }
}

void Minesweeper::GenerateMineField(int mines, Vector2Int excludePosition) {
    std::srand(std::time(nullptr));
    _mines = mines;
    int mineCounter = 0;


    while (mineCounter < mines) {
        int xPos = std::rand() % _size.X;
        int yPos = std::rand() % _size.Y;
        Vector2Int pos(xPos, yPos);
        Tile* tile = _mineField[pos];

        if (pos == excludePosition || tile->HasMine()) {
            continue;
        }

        tile->SetMine(true);
        IncreaseValueSourroundingTiles(pos);
        mineCounter = mineCounter + 1;
    }

    _isInit = true;
}

Vector2Int Minesweeper::GetSize() {
    return _size;
}

Tile* Minesweeper::GetTile(Vector2Int position) {
    return _mineField[position];
}

void Minesweeper::PreRender() {
    for (const auto& tile : _mineField) {
        tile.second->PreRender();
    }
}

void Minesweeper::Render() {
    for (const auto& tile : _mineField) {
        tile.second->Render();
    }
}

void Minesweeper::Reset() {
    for (const auto& tile : _mineField) {
        tile.second->Reset();
    }
    _isInit = false;
    _remainingFields = _size.X * _size.Y;
}

void Minesweeper::LeftClickOnPosition(Vector2Int position) {
    position = position - Vector2Int(100, 0);
    int xPos = position.X / 50;
    int yPos = position.Y / 50;
    Vector2Int tilePos(xPos, yPos);

    LeftClickClickTile(tilePos);

}

void Minesweeper::RightClickOnPosition(Vector2Int position) {
    position = position - Vector2Int(100, 0);
    int xPos = position.X / 50;
    int yPos = position.Y / 50;
    Vector2Int tilePos(xPos, yPos);


    if (_mineField.find(tilePos) != _mineField.end()) {
        Tile* tile = _mineField[tilePos];
        if (tile->CanBeClicked()) {
            tile->ToogleFlagState();
        }

    }
}



void Minesweeper::IncreaseValueSourroundingTiles(Vector2Int pos) {

    Vector2Int tilePos = pos + Vector2Int::VectorLeft + Vector2Int::VectorDown;
    if (_mineField.find(tilePos) != _mineField.end()) {
        _mineField[tilePos]->IncreaseValueByOne();
    }

    tilePos = pos + Vector2Int::VectorLeft;
    if (_mineField.find(tilePos) != _mineField.end()) {
        _mineField[tilePos]->IncreaseValueByOne();
    }

    tilePos = pos + Vector2Int::VectorLeft + Vector2Int::VectorUp;
    if (_mineField.find(tilePos) != _mineField.end()) {
        _mineField[tilePos]->IncreaseValueByOne();
    }

    tilePos = pos + Vector2Int::VectorUp;
    if (_mineField.find(tilePos) != _mineField.end()) {
        _mineField[tilePos]->IncreaseValueByOne();
    }

    tilePos = pos + Vector2Int::VectorUp + Vector2Int::VectorRight;
    if (_mineField.find(tilePos) != _mineField.end()) {
        _mineField[tilePos]->IncreaseValueByOne();
    }

    tilePos = pos + Vector2Int::VectorRight;
    if (_mineField.find(tilePos) != _mineField.end()) {
        _mineField[tilePos]->IncreaseValueByOne();
    }

    tilePos = pos + Vector2Int::VectorRight + Vector2Int::VectorDown;
    if (_mineField.find(tilePos) != _mineField.end()) {
        _mineField[tilePos]->IncreaseValueByOne();
    }

    tilePos = pos + Vector2Int::VectorDown;
    if (_mineField.find(tilePos) != _mineField.end()) {
        _mineField[tilePos]->IncreaseValueByOne();
    }


}

void Minesweeper::LeftClickSurroundingTiles(Vector2Int position) {
    Vector2Int tilePos = position + Vector2Int::VectorLeft + Vector2Int::VectorDown;
    LeftClickClickTile(tilePos);

    tilePos = position + Vector2Int::VectorLeft;
    LeftClickClickTile(tilePos);

    tilePos = position + Vector2Int::VectorLeft + Vector2Int::VectorUp;
    LeftClickClickTile(tilePos);

    tilePos = position + Vector2Int::VectorUp;
    LeftClickClickTile(tilePos);

    tilePos = position + Vector2Int::VectorUp + Vector2Int::VectorRight;
    LeftClickClickTile(tilePos);

    tilePos = position + Vector2Int::VectorRight;
    LeftClickClickTile(tilePos);

    tilePos = position + Vector2Int::VectorRight + Vector2Int::VectorDown;
    LeftClickClickTile(tilePos);

    tilePos = position + Vector2Int::VectorDown;
    LeftClickClickTile(tilePos);
}

void Minesweeper::LeftClickClickTile(Vector2Int position) {

    if (_mineField.find(position) != _mineField.end()) {
        if (_isInit == false) {
            GenerateMineField(10, position);
        }
        Tile* tile = _mineField[position];
        if (tile->CanBeClicked() == false) {
            return;
        }
        if (tile->HasMine()) {
            tile->ShowMine();
            for (auto& pair : _mineField) {
                if (pair.second->HasMine()) {
                    pair.second->ShowMine();
                }
                else {
                    pair.second->DisableClick();
                }
            }
        }
        else {
            tile->ShowValue();
            _remainingFields = _remainingFields - 1;
            if (tile->GetValue() == 0) {
                LeftClickSurroundingTiles(position);
            }
            if (_remainingFields <= _mines) {
                for (auto& pair : _mineField) {
                    if (pair.second->HasMine()) {
                        pair.second->ShowMineClear();
                    }
                    else {
                        pair.second->DisableClick();
                    }
                }
            }
        }

    }

}
