/*
math_utils.hpp

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
#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

#include <SFML/System/Vector3.hpp>

#include <Thor/Vectors/VectorAlgebra3D.hpp>

#include "common.hpp"

Direction rotate(const Direction& vector, const Direction& axis, real_type radians)
{
    const real_type cos_theta = cos(radians);
    const real_type sin_theta = sin(radians);

    const auto rotated = (vector * cos_theta) + (thor::crossProduct(axis, vector) * sin_theta)
                                              + (axis * thor::dotProduct(axis, vector)) * (1 - cos_theta);

    return rotated;
}

#endif // MATH_UTILS_HPP
