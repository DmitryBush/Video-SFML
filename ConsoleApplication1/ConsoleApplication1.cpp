#include <iostream>
#include "SFML/Graphics.hpp"
#include <Windows.h>
#include <chrono>
#include "video_sfml.h"

int main()
{
    /*sf::Image mov;
    sf::Texture tex;
 auto startTime = std::chrono::steady_clock::now();
    mov.loadFromFile("Resource//test//0000_BigFile.png");
    tex.loadFromImage(mov);
   
    auto endTime = std::chrono::steady_clock::now();
    std::cout << "Time elapsed - "
        << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << '\n';*/
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(1280,
        720), "Cutscene", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    video_sfml video("Resource//cutscene//", 298, 60, window);
    video.Prebuffering(120);
    video.StartStreaming();
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
        window.clear();
        video.VideoShow(window);
        window.display();
    }
    return 0;
}
