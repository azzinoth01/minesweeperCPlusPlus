#include "Color.h"

Color::Color() {

    ColorValue[0] = 1.0f;
    ColorValue[1] = 1.0f;
    ColorValue[2] = 1.0f;
    ColorValue[3] = 1.0f;
}

Color::Color(float r, float g, float b, float a) {
    ColorValue[0] = r;
    ColorValue[1] = g;
    ColorValue[2] = b;
    ColorValue[3] = a;
}

Color Color::Black = Color{ 0,0,0,1 };
Color Color::White = Color{ 1,1,1,1 };
Color Color::Red = Color{ 1,0,0,1 };
Color Color::Green = Color{ 0,1,0,1 };
Color Color::Blue = Color{ 0,0,1,1 };

