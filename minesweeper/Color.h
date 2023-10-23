#pragma once


struct Color {

public:

    float ColorValue[4];
    void SetR(float r) {
        ColorValue[0] = r;
    }
    float GetR() {
        return  ColorValue[0];
    }
    void SetG(float g) {
        ColorValue[1] = g;
    }
    float GetG() {
        return  ColorValue[1];
    }
    void SetB(float b) {
        ColorValue[2] = b;
    }
    float GetB() {
        return  ColorValue[2];
    }
    void SetA(float a) {
        ColorValue[3] = a;
    }
    float GetA() {
        return  ColorValue[3];
    }

    Color();
    Color(float r, float g, float b, float a = 1.0f);

    static Color Black;
    static Color White;
    static Color Red;
    static Color Green;
    static Color Blue;
};

