#include <iostream>
#include "SFML/Graphics.hpp"
#include <Windows.h>
#include <chrono>
#include <thread>

int main()
{
    const int VIDEO_FPS = 1000000 / 60;

    sf::Image mov[300];
    sf::Texture image;
    sf::Sprite a;

    std::string path = "Resource//cutscene//";
    std::string prefix;

    register unsigned int ready_frame = 0;
    auto startTime = std::chrono::steady_clock::now();
    for (ready_frame = 0; ready_frame < 121; ready_frame++)
    {
        if (ready_frame < 10)
        {
            prefix = "000" + std::to_string(ready_frame) + ".png";
            //path = "Resource//cutscene//000" + std::to_string(ready_frame) + ".png";
        }
        else if (ready_frame < 100)
        {
            prefix = "00" + std::to_string(ready_frame) + ".png";
            //path = "Resource//cutscene//00" + std::to_string(ready_frame) + ".png";
        }
        else if (ready_frame < 1000)
        {
            prefix = "0" + std::to_string(ready_frame) + ".png";
            //path = "Resource//cutscene//0" + std::to_string(ready_frame) + ".png";
        }
        mov[ready_frame].loadFromFile(path + prefix);
        std::cout << "loaded" << ready_frame << std::endl;
    }
    auto endTime = std::chrono::steady_clock::now();
    std::cout << "Time elapsed - "
        << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << '\n';
    int passedTime = 0;
    register unsigned int curr_frame = 0;
    register unsigned int frame_cleaner = 0;
    

    a.setOrigin(sf::Vector2f(640.f,360.f));
    a.setPosition(640.f, 360.f);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(1280,
        720), "Cutscene", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::Clock clock;
    while (true)
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            sf::Vector2f mousePos(static_cast<float>(sf::Mouse::getPosition(window).x),
                static_cast<float>(sf::Mouse::getPosition(window).y));

            
        }

        if (ready_frame != 299)
        {
            if (ready_frame < 10)
            {
                path = "Resource//cutscene//000" + std::to_string(ready_frame) + ".png";
                mov[ready_frame].loadFromFile(path);
                ready_frame++;
            }
            else if (ready_frame < 100)
            {
                path = "Resource//cutscene//00" + std::to_string(ready_frame) + ".png";
                mov[ready_frame].loadFromFile(path);
                ready_frame++;
            }
            else if (ready_frame < 1000)
            {
                path = "Resource//cutscene//0" + std::to_string(ready_frame) + ".png";
                mov[ready_frame].loadFromFile(path);
                ready_frame++;
            }
        }
        
        
        if (passedTime >= VIDEO_FPS && curr_frame != 299)
        {
            passedTime = static_cast<int>(clock.restart().asMicroseconds());
            if (curr_frame <= ready_frame)
            {
                image.loadFromImage(mov[curr_frame]);
                a.setTexture(image);
                curr_frame++;

                window.clear();

                window.draw(a);

                window.display();
            }
            else
            {
                std::cout << "frame skipping" << '\n';
            }
        }
        else if (passedTime < VIDEO_FPS) { passedTime += static_cast<int>(clock.restart().asMicroseconds()); }
        else if (curr_frame == 299) { break; }

        if (curr_frame > frame_cleaner && frame_cleaner != 299)
        {
            mov[frame_cleaner].~Image();
            frame_cleaner++;
        }
    }
    return 0;
}
