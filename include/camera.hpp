/*
camera.hpp

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
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/System/Vector3.hpp>

#include "common.hpp"

class Ray;

class Camera
{
public:
    Camera(const Point& origin, const Direction& dir, real_type fov = 90, real_type aspect_ratio = 1);

    Point& origin();
    Point origin() const;
    void set_origin(const Point& pt);

    Direction direction() const;
    void set_direction(const Direction& value);

    real_type fov() const;
    void set_fov(const real_type &value);

    real_type aspect_ratio() const;
    void set_aspect_ratio(const real_type &value);

    Direction up_vector() const;
    Direction right_vector() const;

    /* u,v € ]-1;1[ */
    Ray cast_ray(real_type u, real_type v) const;

private:
    real_type m_fov;
    real_type m_aspect_ratio;
    Point     m_origin;
    Direction m_direction;
    Direction m_up_vector;
    Direction m_right_vector;

    real_type m_x_width;
    real_type m_y_width;
};

#endif // CAMERA_HPP
