/*
%{Cpp:License:FileName}

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
#include <iostream>

#include <SFML/Graphics.hpp>
#include <Thor/Graphics/ColorGradient.hpp>

#include "camera.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "light_source.hpp"
#include "math_utils.hpp"
#include "ostream_interface.hpp"

#include "scene.hpp"

void redraw(size_t w, size_t h, const Camera& cam, const Scene& scene, sf::Color* pixels)
{
#pragma omp parallel for schedule(dynamic)
    for (size_t j = 0; j < h; ++j)
    {
        for (size_t i = 0; i < w; ++i)
        {
            auto ray = cam.cast_ray(2.0*i/w - 1, 1 - 2.0*j/h);
            pixels[j*w + i] = scene.ray_color(ray);
        }
    }
}

int main()
{
    Camera cam{{-8, 0, 0}, {1, 0, 0}, 90};
    cam.set_aspect_ratio(640.0/480);

    sf::Image grid;
    grid.loadFromFile("grid.png");

    sf::Image space;
    space.loadFromFile("pepe.png");

    sf::Image wojak;
    wojak.loadFromFile("wojak.jpg");

    Scene scene;
    scene.shader = diffuse_shading;
    scene.lights.emplace_back(std::make_unique<LightSource>(Point{10, 10, 10}, 200, sf::Color::White));
    scene.lights.emplace_back(std::make_unique<LightSource>(Point{-10, -10, 10}, 200, sf::Color::White));
    scene.objects.emplace_back(std::make_unique<Sphere>(Point{5, 0, 0}, 4, Material{grid}));
    scene.objects.emplace_back(std::make_unique<Sphere>(Point{8, 5, 5}, 2, Material{wojak}));
    scene.objects.emplace_back(std::make_unique<Sphere>(Point{5, -20, 5}, 2, Material{sf::Color::Yellow}));
    scene.objects.emplace_back(std::make_unique<Sphere>(Point{5, 20, 5}, 3, Material{sf::Color::Magenta}));
    auto plane = std::make_unique<Plane>(Point{0, 0, -10}, Direction{0, 0, 1}, Material{grid});
    plane->texture_scale = 10;
    scene.objects.emplace_back(std::move(plane));

    const size_t width = 640;
    const size_t height = 480;

    sf::RenderWindow window(sf::VideoMode(width, height), "SFML window");

    sf::Color pixels[width * height];

    sf::Texture texture;
    texture.create(width, height);

    sf::Sprite sprite(texture);
    sf::Clock clock;

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Q:
                        cam.set_direction(rotate(cam.direction(), cam.up_vector(), M_PI/12));
                        break;
                    case sf::Keyboard::D:
                        cam.set_direction(rotate(cam.direction(), cam.up_vector(), -M_PI/12));
                        break;
                    case sf::Keyboard::Z:
                        cam.set_direction(rotate(cam.direction(), cam.right_vector(), M_PI/12));
                        break;
                    case sf::Keyboard::S:
                        cam.set_direction(rotate(cam.direction(), cam.right_vector(), -M_PI/12));
                        break;
                    case sf::Keyboard::Left:
                        cam.origin() -= cam.right_vector();
                        break;
                    case sf::Keyboard::Right:
                        cam.origin() += cam.right_vector();
                        break;
                    case sf::Keyboard::Up:
                        cam.origin() += cam.direction();
                        break;
                    case sf::Keyboard::Down:
                        cam.origin() -= cam.direction();
                        break;
                    case sf::Keyboard::Add:
                        cam.origin() += cam.up_vector();
                        break;
                    case sf::Keyboard::Subtract:
                        cam.origin() -= cam.up_vector();
                        break;
                    default:
                        break;
                }
            }
        }
        // Clear screen
        window.clear();

        redraw(width, height, cam, scene, pixels);

        texture.update((const sf::Uint8*)pixels);

        window.draw(sprite);
        // Update the window
        window.display();

        std::cerr << "FPS :" << 1/clock.restart().asSeconds() << "\n";
    }
    return 0;
}
