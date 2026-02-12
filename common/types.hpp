#pragma once

struct Vec2
{
    float x;
    float y;

    // Constructors
    constexpr Vec2() noexcept : x(0.0f), y(0.0f) {}
    constexpr Vec2(float x_, float y_) : x(x_), y(y_) {}

    // Basic arithmetic
    constexpr Vec2 operator+(const Vec2& other) const noexcept
    {
        return { x + other.x, y + other.y };
    }

    constexpr Vec2 operator-(const Vec2& other) const noexcept
    {
        return { x - other.x, y - other.y };
    }

    constexpr Vec2 operator*(float scalar) const noexcept
    {
        return { x * scalar, y * scalar };
    }

    constexpr Vec2 operator/(float scalar) const noexcept
    {
        return { x / scalar, y / scalar };
    }

    Vec2& operator+=(const Vec2& other) noexcept
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& other) noexcept
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2& operator*=(float scalar) noexcept
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vec2& operator/=(float scalar) noexcept
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Magnitude
    float length() const noexcept
    {
        return std::sqrt(x * x + y * y);
    }

    float lengthSquared() const noexcept
    {
        return x * x + y * y;
    }

    // Normalize (safe)
    Vec2 normalized() const noexcept
    {
        float len = length();
        if (len == 0.0f)
            return {0.0f, 0.0f};
        return { x / len, y / len };
    }
};