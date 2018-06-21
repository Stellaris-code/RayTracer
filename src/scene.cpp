/*
scene.cpp

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

#include "scene.hpp"

#include <Thor/Graphics/ColorGradient.hpp>

#include "ray.hpp"
#include "shape.hpp"
#include "light_source.hpp"

std::optional<HitResult> Scene::do_raycast(const Ray &ray) const
{
#if 1
    std::optional<HitResult> best_hit;
    real_type best_dist;
    for (size_t i { 0 }; i < objects.size(); ++i)
    {
        const auto& obj = objects[i];
        if (auto hit = obj->intersection_point(ray); hit)
        {
            const real_type dist = thor::squaredLength(hit->point - ray.origin());
            if (!best_hit || dist < best_dist)
            {
                best_hit = *hit;
                best_dist = dist;
            }
        }
    }

    return best_hit;
#else
    for (size_t i { 0 }; i < objects.size(); ++i)
    {
        const auto& obj = objects[i];
        if (auto hit = obj->intersection_point(ray); hit)
        {
            return *hit;
        }
    }

    return {};
#endif
}

sf::Color Scene::ray_color(const Ray &ray) const
{
    return compute_ray_color(ray, 0);
}

sf::Color Scene::compute_ray_color(const Ray &ray, size_t depth) const
{
    if (depth >= max_ray_depth)
        return background_color;

    auto hit = do_raycast(ray);
    if (hit)
    {
        std::vector<std::reference_wrapper<const LightSource>> visible_lights;

        for (const auto& light : lights)
        {
            const auto new_direction = light->position - hit->point;
            if (!do_raycast(Ray{hit->point + new_direction*shadow_bias, new_direction}))
            {
                visible_lights.emplace_back(*light);
            }
        }

        return shader(*hit, visible_lights);
    }

    return background_color;
}
