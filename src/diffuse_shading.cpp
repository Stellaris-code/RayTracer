/*
diffuse_shading.cpp

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

#include "shading.hpp"

#include <Thor/Vectors/VectorAlgebra3D.hpp>
#include <iostream>

#include "color_utils.hpp"
#include "shape.hpp"

sf::Color diffuse_shading(const HitResult& result,
                          const std::vector<std::reference_wrapper<const LightSource>>& lights)
{
    if (lights.empty())
    {
        return integer_color(normalized_color(result.obj->material.color(result.tex_coords))*real_type{0.05});
    }

    sf::Vector3<real_type> color = normalized_color(result.obj->material.color(result.tex_coords))*real_type{0.05};

    for (const auto& light : lights)
    {
        const real_type cos_theta =
                std::max<real_type>(thor::dotProduct(result.normal,
                                                     thor::unitVector(light.get().position - result.point)), 0.0);

        const real_type squared_distance = thor::squaredLength(light.get().position - result.point);

        sf::Vector3<real_type> normalized;
        normalized = thor::cwiseProduct(normalized_color(result.obj->material.color(result.tex_coords)),
                                        normalized_color(light.get().color));
        color += normalized * light.get().intensity * cos_theta
                               / squared_distance;
    }

    return integer_color(color);
}
