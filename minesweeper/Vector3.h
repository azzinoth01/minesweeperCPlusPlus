#pragma once
struct Vector3 {

public:
    float X;
    float Y;
    float Z;

    Vector3(float x = 0, float y = 0, float z = 0);

    Vector3& operator+=(const Vector3& b);
    Vector3& operator-=(const Vector3& b);
    Vector3& operator*=(const Vector3& b);
    Vector3& operator/=(const Vector3& b);

    Vector3 operator+(const Vector3& b);
    Vector3 operator-(const Vector3& b);
    Vector3 operator*(const Vector3& b);
    Vector3 operator/(const Vector3& b);

    Vector3 operator*(const float b);
    Vector3 operator/(const float b);

    static Vector3 VectorZero;
    static Vector3 VectorLeft;
    static Vector3 VectorRight;
    static Vector3 VectorUp;
    static Vector3 VectorDown;
    static Vector3 VectorForward;
    static Vector3 VectorBackward;
};

