/*
plane.cpp

Copyright (c) 19 Yann BOUCHER (yann)

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

#include "plane.hpp"
#include "ray.hpp"

#include <Thor/Vectors/VectorAlgebra3D.hpp>

Plane::Plane(const Point &i_point, const Direction &i_vector, const Material& mat)
    : Shape(mat), point(i_point), vector(i_vector)
{
}

std::optional<HitResult> Plane::intersection_point(const Ray& ray    ) const
{
    const real_type d = thor::dotProduct(vector, point);

    const real_type t = (-thor::dotProduct(vector, ray.origin()) + d) /
                        ( thor::dotProduct(vector, ray.direction()));

    if (t > 0)
    {
        auto point = ray.point_at(t);
        HitResult result { this, point, vector, tex_coords(point) };
        return result;
    }
    else
        return {};
}

sf::Vector2<real_type> Plane::tex_coords(const Point &pt) const
{
    auto u = Direction{vector.y, vector.z, -vector.x};
    auto v = thor::crossProduct(vector, u);

    real_type u_coord = std::fmod(1 + std::fmod(thor::dotProduct(u, pt)/texture_scale, 1), 1);
    real_type v_coord = std::fmod(1 + std::fmod(thor::dotProduct(v, pt)/texture_scale, 1), 1);

    return {u_coord, v_coord};
}
