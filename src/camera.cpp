/*
camera.cpp

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

#include "camera.hpp"
#include "ray.hpp"

#include <cmath>
#include <iostream>

#include <Thor/Math/Trigonometry.hpp>

Camera::Camera(const Point &origin, const Direction &dir, real_type fov, real_type aspect_ratio)
{
    set_origin(origin);
    set_direction(dir);
    set_fov(fov);
    set_aspect_ratio(aspect_ratio);
}

Point &Camera::origin()
{
    return m_origin;
}

Point Camera::origin() const
{
    return m_origin;
}

void Camera::set_origin(const Point &pt)
{
    m_origin = pt;
}

Direction Camera::direction() const
{
    return m_direction;
}

void Camera::set_direction(const Direction &value)
{
    m_direction = thor::unitVector(value);
    m_up_vector = thor::unitVector(thor::crossProduct(direction(), {0, 1, 0}));
    m_right_vector = thor::unitVector(-thor::crossProduct(direction(), m_up_vector));
}

real_type Camera::fov() const
{
    return m_fov;
}

void Camera::set_fov(const real_type &value)
{
    m_fov = value;
    m_x_width = tan(thor::toRadian(fov()/2));
    m_y_width = tan(thor::toRadian(fov()/2)) / aspect_ratio();
}

real_type Camera::aspect_ratio() const
{
    return m_aspect_ratio;
}

void Camera::set_aspect_ratio(const real_type &value)
{
    m_aspect_ratio = value;
    m_y_width = tan(thor::toRadian(fov()/2)) * aspect_ratio();
}

Direction Camera::up_vector() const
{
    return m_up_vector;
}

Direction Camera::right_vector() const
{
    return m_right_vector;
}

Ray Camera::cast_ray(real_type u, real_type v) const
{
    Ray ray;
    ray.set_origin(origin());

    real_type x_offset = u/m_x_width;
    real_type y_offset = v/m_y_width;

    Direction ray_dir = direction();
    ray_dir += right_vector()*x_offset;
    ray_dir += up_vector   ()*y_offset;

    ray.set_direction(ray_dir);

    return ray;
}
