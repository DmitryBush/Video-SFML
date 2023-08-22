#include <iostream>
#include "SFML/Graphics.hpp"
#include <chrono>
#include "video_sfml.h"
#include "fpng.h"

int main()
{
    //auto startTime = std::chrono::steady_clock::now();
    //auto endTime = std::chrono::steady_clock::now();
    /*std::cout << "Time elapsed - "
        << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << '\n';*/
    

    system("pause");
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(1920,
        1080), "Cutscene", sf::Style::Fullscreen, settings);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    video_sfml video("Resource//cutscene//", 298, 60, window);
    video.Prebuffering(120);
    video.Start();
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
