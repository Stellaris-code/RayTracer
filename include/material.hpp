/*
material.hpp

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
#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>

#include "common.hpp"

struct Material
{
    Material(const sf::Color color)
        : diffuse_color(color), texture(nullptr)
    {}

    Material(const sf::Image& img)
        : texture(&img)
    {}

    sf::Color color(const sf::Vector2<real_type>& tex_coords) const
    {
        if (texture == nullptr)
            return diffuse_color;
        else
        {
            return texture->getPixel(std::min<size_t>(tex_coords.x * texture->getSize().x, texture->getSize().x-1),
                                     std::min<size_t>(tex_coords.y * texture->getSize().y, texture->getSize().y-1));
        }
    }

    sf::Color diffuse_color;
    const sf::Image* texture { nullptr };
};

#endif // MATERIAL_HPP
