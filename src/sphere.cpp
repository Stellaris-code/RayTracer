/*
sphere.cpp

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

#include "sphere.hpp"

#include "ray.hpp"

#include <cmath>

Sphere::Sphere(const Point &i_origin, real_type i_radius, const Material &mat)
    : Shape(mat), center(i_origin), radius_sq(i_radius*i_radius)
{
}

std::optional<HitResult> Sphere::intersection_point(const Ray &ray) const
{
    const real_type A = 1; // Since the direction is an unit vector
    const real_type B = thor::dotProduct(ray.direction(), ray.origin()-center);
    const real_type C = thor::squaredLength(ray.origin()-center) - radius_sq;

    const real_type discriminant = B*B - A*C;
    if (discriminant < 0)
        return {};

    const real_type square_root = std::sqrt(discriminant);

    const real_type sol = (-B-square_root);

    if (sol > 0)
    {
        const auto point = ray.point_at(sol);
        const auto normal = thor::unitVector(point - center);
        HitResult result { this, point, normal, tex_coords(normal) };
        return result;
    }

    return {};
}

sf::Vector2<real_type> Sphere::tex_coords(const Direction &normal)
{
    sf::Vector2<real_type> coords;
    coords.x = 0.5 + atan2(normal.y, normal.x) / (2*M_PI);
    coords.y = 0.5 - normal.z/2;

    assert(coords.x >= 0 && coords.y >= 0 && coords.x <= 1 && coords.y <= 1);

    coords.x = std::fmod(coords.x + real_type{0.5}, 1);

    return coords;
}
