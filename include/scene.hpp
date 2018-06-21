/*
scene.hpp

Copyright (c) 17 Yann BOUCHER (yann)

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
#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include <optional>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector3.hpp>

#include "shading.hpp"
#include "hit_result.hpp"
#include "common.hpp"

class Shape;
class LightSource;
class Ray;

class Scene
{
public:
    static constexpr size_t max_ray_depth = 32;

    sf::Color background_color = sf::Color::Black;
    real_type shadow_bias = 0.000001;
    shading_function shader = flat_shading;

    std::vector<std::unique_ptr<Shape>>       objects;
    std::vector<std::unique_ptr<LightSource>> lights;

    std::optional<HitResult> do_raycast(const Ray& ray) const;
    sf::Color ray_color(const Ray& ray) const;

private:
    sf::Color compute_ray_color(const Ray& ray, size_t depth) const;
};

#endif // SCENE_HPP
