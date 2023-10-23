#include "Vector3.h"

Vector3::Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {
}

Vector3& Vector3::operator+=(const Vector3& b) {
    X = X + b.X;
    Y = Y + b.Y;
    Z = Z + b.Z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& b) {
    X = X - b.X;
    Y = Y - b.Y;
    Z = Z - b.Z;
    return *this;
}

Vector3& Vector3::operator*=(const Vector3& b) {
    X = X * b.X;
    Y = Y * b.Y;
    Z = Z * b.Z;
    return *this;
}

Vector3& Vector3::operator/=(const Vector3& b) {
    X = X / b.X;
    Y = Y / b.Y;
    Z = Z / b.Z;
    return *this;
}

Vector3 Vector3::operator+(const Vector3& b) {
    Vector3 v3;
    v3.X = X + b.X;
    v3.Y = Y + b.Y;
    v3.Z = Z + b.Z;
    return v3;
}

Vector3 Vector3::operator-(const Vector3& b) {
    Vector3 v3;
    v3.X = X - b.X;
    v3.Y = Y - b.Y;
    v3.Z = Z - b.Z;
    return v3;
}

Vector3 Vector3::operator*(const Vector3& b) {
    Vector3 v3;
    v3.X = X * b.X;
    v3.Y = Y * b.Y;
    v3.Z = Z * b.Z;
    return v3;
}

Vector3 Vector3::operator/(const Vector3& b) {
    Vector3 v3;
    v3.X = X / b.X;
    v3.Y = Y / b.Y;
    v3.Z = Z / b.Z;
    return v3;
}

Vector3 Vector3::operator*(const float b) {
    Vector3 v3;
    v3.X = X * b;
    v3.Y = Y * b;
    v3.Z = Z * b;
    return v3;
}

Vector3 Vector3::operator/(const float b) {
    Vector3 v3;
    v3.X = X / b;
    v3.Y = Y / b;
    v3.Z = Z / b;
    return v3;
}

Vector3 Vector3::VectorZero = Vector3(0, 0, 0);
Vector3 Vector3::VectorLeft = Vector3(-1, 0, 0);
Vector3 Vector3::VectorRight = Vector3(1, 0, 0);
Vector3 Vector3::VectorUp = Vector3(0, 1, 0);
Vector3 Vector3::VectorDown = Vector3(0, -1, 0);
Vector3 Vector3::VectorForward = Vector3(0, 0, 1);
Vector3 Vector3::VectorBackward = Vector3(0, 0, -1);
