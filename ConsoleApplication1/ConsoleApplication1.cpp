#include <iostream>
#include "SFML/Graphics.hpp"
#include <Windows.h>
#include <chrono>
#include "video_sfml.h"
#include "fpng.h"

int main()
{
    /*std::vector<uint8_t> fpngd_decode_buffer;
    std::vector<uint8_t> fpng_file_buf;
    uint32_t channels_in_file;
    uint32_t decoded_width, decoded_height;
    uint32_t desired_chans = 4;
    fpng::fpng_init();
    if(fpng::fpng_decode_file("fpng.png",
        fpngd_decode_buffer, decoded_width, decoded_height, channels_in_file, desired_chans) 
        == fpng::FPNG_DECODE_SUCCESS)
    {
        std::cout << "uspex";
    }
    else
    {
        std::cout << "ne uspex";
    }*/

    //system("pause");
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(1280,
        720), "Cutscene", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    video_sfml video("Resource//cutscene//", 298, 120, window);
    video.Prebuffering(120);
    video.StartStreaming();
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
