#include "Vector2Int.h"


Vector2Int::Vector2Int(float x, float y) : X(x), Y(y) {
}

Vector2Int& Vector2Int::operator+=(const Vector2Int& b) {
    X = X + b.X;
    Y = Y + b.Y;

    return *this;
}

Vector2Int& Vector2Int::operator-=(const Vector2Int& b) {
    X = X - b.X;
    Y = Y - b.Y;

    return *this;
}

Vector2Int& Vector2Int::operator*=(const Vector2Int& b) {
    X = X * b.X;
    Y = Y * b.Y;

    return *this;
}

Vector2Int& Vector2Int::operator/=(const Vector2Int& b) {
    X = X / b.X;
    Y = Y / b.Y;

    return *this;
}

Vector2Int Vector2Int::operator+(const Vector2Int& b) {
    Vector2Int v3;
    v3.X = X + b.X;
    v3.Y = Y + b.Y;

    return v3;
}

Vector2Int Vector2Int::operator-(const Vector2Int& b) {
    Vector2Int v3;
    v3.X = X - b.X;
    v3.Y = Y - b.Y;

    return v3;
}

Vector2Int Vector2Int::operator*(const Vector2Int& b) {
    Vector2Int v3;
    v3.X = X * b.X;
    v3.Y = Y * b.Y;

    return v3;
}

Vector2Int Vector2Int::operator/(const Vector2Int& b) {
    Vector2Int v3;
    v3.X = X / b.X;
    v3.Y = Y / b.Y;

    return v3;
}

Vector2Int Vector2Int::operator*(const float b) {
    Vector2Int v3;
    v3.X = X * b;
    v3.Y = Y * b;

    return v3;
}

Vector2Int Vector2Int::operator/(const float b) {
    Vector2Int v3;
    v3.X = X / b;
    v3.Y = Y / b;

    return v3;
}

bool Vector2Int::operator<(const Vector2Int& b) const {
    if (X < b.X) {
        return true;
    }
    if (X > b.X) {
        return false;
    }

    return Y < b.Y;
}

bool Vector2Int::operator==(const Vector2Int& b) const {
    return X == b.X && Y == b.Y;

}

Vector2Int Vector2Int::VectorZero = Vector2Int(0, 0);
Vector2Int Vector2Int::VectorLeft = Vector2Int(-1, 0);
Vector2Int Vector2Int::VectorRight = Vector2Int(1, 0);
Vector2Int Vector2Int::VectorUp = Vector2Int(0, 1);
Vector2Int Vector2Int::VectorDown = Vector2Int(0, -1);

