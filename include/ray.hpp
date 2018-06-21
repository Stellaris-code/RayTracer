/*
ray.hpp

Copyright (c) 16 Yann BOUCHER (yann)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#ifndef RAY_HPP
#define RAY_HPP

#include <SFML/System/Vector3.hpp>
#include <Thor/Vectors/VectorAlgebra3D.hpp>

#include "common.hpp"

class Ray
{
public:
    Ray() = default;
    Ray(const Point& origin, const Direction& dir)
    {
        m_origin = origin;
        set_direction(dir);
    }

    Point point_at(real_type t) const
    {
        return {m_origin + m_direction*t};
    }

    Point origin() const
    {

        return m_origin;
    }
    Direction direction() const
    {
        return m_direction;
    }

    void set_origin   (const Point& origin)
    {
        m_origin    = origin;
    }
    void set_direction(const Direction& dir)
    {
        m_direction = thor::unitVector(dir);
    }
    void set_normalized_direction(const Direction& dir)
    {
        m_direction = dir;
    }
private:
    Point     m_origin;
    Direction m_direction;
};

inline Ray reflection(const Ray& ray, const Point& point, const Direction& normal)
{
    return Ray{point, ray.direction() - 2 * thor::dotProduct(normal, ray.direction()) * normal};
}

#endif // RAY_HPP
