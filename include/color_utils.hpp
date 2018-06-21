/*
color_utils.hpp

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
#ifndef COLOR_UTILS_HPP
#define COLOR_UTILS_HPP

#include "common.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector3.hpp>
#include <Thor/Vectors/VectorAlgebra3D.hpp>

#include <cassert>

inline sf::Vector3<real_type> normalized_color(const sf::Color& color)
{
    return {color.r/real_type{255.0},
        color.g/real_type{255.0},
        color.b/real_type{255.0}};
}

inline sf::Color integer_color(const sf::Vector3<real_type>& normalized)
{
    return {static_cast<sf::Uint8>(std::min<real_type>(normalized.x, 1.0)*255),
            static_cast<sf::Uint8>(std::min<real_type>(normalized.y, 1.0)*255),
            static_cast<sf::Uint8>(std::min<real_type>(normalized.z, 1.0)*255)};
}

#endif // COLOR_UTILS_HPP
