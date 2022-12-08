#pragma once
#include "pch.h"

struct Color
{
public:
    Color() { r = 255; g = 255; b = 255; }
    Color(int _r, int _g, int _b) 
    { 
        r = _r; 
        g = _g; 
        b = _b; 
    
        if (r > 255) r = 255;
        if (r < 0) r = 0;

        if (g > 255) g = 255;
        if (g < 0) g = 0;

        if (b > 255) b = 255;
        if (b < 0) b = 0;
    }
    ~Color() {}

public:
    // TODO : 내장함수들

public:
    int r;
    int g;
    int b;

public:
    Color operator+ (const Color& C) { return Color(r + C.r, g + C.g, b + C.b); }
    Color operator- (const Color& C) { return Color(r - C.r, g + C.g, b + C.b); }
    Color operator* (float S) { return Color(r * S, g * S, b * S); }
    Color operator/ (float S) { return Color(r / S, g / S, b / S);
    }
};