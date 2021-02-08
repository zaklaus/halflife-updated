/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#pragma once

#include "math.h"
#include "types.h"
#include "Vector2D.h"

/// <summary>
/// 3D Vector - same data-layout as engine's vec3_t, which is a vec_t[3]
/// </summary>
class Vector
{
public:
    // Construction/destruction
    Vector()
    {
        x = y = z = 0;
    }

    Vector(const float x, const float y, const float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    //Vector(const double x, const double y, const double z)
    //{
    //    this->x = static_cast<float>(x);
    //    this->y = static_cast<float>(y);
    //    this->z = static_cast<float>(z);
    //}

    //Vector(const int x, const int y, const int z)
    //{
    //    this->x = static_cast<float>(x);
    //    this->y = static_cast<float>(y);
    //    this->z = static_cast<float>(z);
    //}

    Vector(const Vector &v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
    }

    Vector(Vector&&) noexcept = default;

    Vector(const float rgfl[3])
    {
        x = rgfl[0];
        y = rgfl[1];
        z = rgfl[2];
    }

    ~Vector() = default;
    Vector& operator=(const Vector& v) = default;
    Vector& operator=(Vector&& v) = default;

    // Operators

    Vector operator-() const
    {
        return Vector(-x, -y, -z);
    }

    int operator==(const Vector& v) const
    {
        return x == v.x && y == v.y && z == v.z;
    }

    int operator!=(const Vector& v) const
    {
        return !(*this == v);
    }

    Vector operator+(const Vector& v) const
    {
        return Vector(x + v.x, y + v.y, z + v.z);
    }

    Vector operator-(const Vector& v) const
    {
        return Vector(x - v.x, y - v.y, z - v.z);
    }

    Vector operator*(const float fl) const
    {
        return Vector(x * fl, y * fl, z * fl);
    }

    Vector operator/(const float fl) const
    {
        return Vector(x / fl, y / fl, z / fl);
    }

    // Methods

    void CopyToArray(float* rgfl) const
    {
        rgfl[0] = x;
        rgfl[1] = y;
        rgfl[2] = z;
    }

    float Length() const
    {
        const auto xx = static_cast<double>(x);
        const auto yy = static_cast<double>(y);
        const auto zz = static_cast<double>(z);
        return static_cast<float>(sqrt(xx * xx + yy * yy + zz * zz));
    }

    float Length2D() const
    {
        const auto xx = static_cast<double>(x);
        const auto yy = static_cast<double>(y);
        return static_cast<float>(sqrt(xx * xx + yy * yy));
    }

    /// <summary>
    /// Vectors will now automatically convert to float * when needed
    /// </summary>
    operator float*()
    {
        return &x;
    }

    /// <summary>
    /// Vectors will now automatically convert to float * when needed
    /// </summary>
    operator const float*() const
    {
        return &x;
    }

    Vector Normalize() const
    {
        auto flLen = Length();
        if (flLen == 0) return Vector(0, 0, 1);
        flLen = 1 / flLen;
        return Vector(x * flLen, y * flLen, z * flLen);
    }

    Vector2D Make2D() const
    {
        return Vector2D(x, y);
    }

    static float DotProduct(const Vector& a, const Vector& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    static Vector CrossProduct(const Vector& a, const Vector& b)
    {
        return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }

    // Members

    vec_t x, y, z;
};

inline Vector operator*(float fl, const Vector& v)
{
    return v * fl;
}

#define vec3_t Vector
