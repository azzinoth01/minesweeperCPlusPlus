#pragma once
struct Vector2Int {

public:
    int X;
    int Y;
    Vector2Int(float x = 0, float y = 0);

    Vector2Int& operator+=(const Vector2Int& b);
    Vector2Int& operator-=(const Vector2Int& b);
    Vector2Int& operator*=(const Vector2Int& b);
    Vector2Int& operator/=(const Vector2Int& b);

    Vector2Int operator+(const Vector2Int& b);
    Vector2Int operator-(const Vector2Int& b);
    Vector2Int operator*(const Vector2Int& b);
    Vector2Int operator/(const Vector2Int& b);

    Vector2Int operator*(const float b);
    Vector2Int operator/(const float b);

    bool operator==(const Vector2Int& b) const;
    bool operator<(const Vector2Int& b) const;

    static Vector2Int VectorZero;
    static Vector2Int VectorLeft;
    static Vector2Int VectorRight;
    static Vector2Int VectorUp;
    static Vector2Int VectorDown;

};

