#pragma once
struct Vector2
{
public:
    Vector2() { x = 0; y = 0; }
    Vector2(float _x, float _y) { x = _x; y = _y; }
    ~Vector2() {}

public:
    // TODO : 내장함수들

public:
    float x;
    float y;

public:
    Vector2 operator+ (const Vector2& V) { return Vector2(x + V.x, y + V.y); }
    Vector2 operator- (const Vector2& V) { return Vector2(x - V.x, y - V.y); }
    Vector2 operator* (float S) { return Vector2(x * S, y * S); }
    Vector2 operator/ (float S) { return Vector2(x / S, y / S); }
    Vector2 operator= (POINT pt) { return Vector2(pt.x, pt.y); }
};