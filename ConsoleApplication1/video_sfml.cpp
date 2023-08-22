#include "video_sfml.h"


void video_sfml::TextureStreaming()
{
    while (ready_frame <= FRAMES)
    {
        auto startTime = std::chrono::steady_clock::now();
        if (ready_frame < 10)
        {
            prefix = "000" + std::to_string(ready_frame) + ".png";
            buffer[ready_frame].loadFromFile(path + prefix);
            ready_frame.store(++ready_frame, std::memory_order_release);
        }
        else if (ready_frame < 100)
        {
            prefix = "00" + std::to_string(ready_frame) + ".png";
            buffer[ready_frame].loadFromFile(path + prefix);
            ready_frame.store(++ready_frame, std::memory_order_release);
        }
        else if (ready_frame < 1000)
        {
            prefix = "0" + std::to_string(ready_frame) + ".png";
            buffer[ready_frame].loadFromFile(path + prefix);
            ready_frame.store(++ready_frame, std::memory_order_release);
        }
        
        auto endTime = std::chrono::steady_clock::now();
        std::cout << "Time elapsed - "
            << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << '\n';
    }
}

void video_sfml::GarbageCollector()
{
    if (curr_frame > frame_mem_cleaner && frame_mem_cleaner <= FRAMES)
    {
        buffer[frame_mem_cleaner].~Image();
        frame_mem_cleaner++;
    }
}

void video_sfml::Play()
{
    track.play();
    while (curr_frame <= FRAMES)
    {
        if (track.getStatus() == sf::Music::Playing || 
            (track.getStatus() == sf::Music::Stopped && curr_frame <= FRAMES))
        {
            //auto startTime = std::chrono::steady_clock::now();
            if (passedTime >= VIDEO_FPS - 200 && curr_frame <= FRAMES)
            {
                if (curr_frame < ready_frame.load(std::memory_order_acquire))
                {
                    if (gpu_texture_loaded)
                    {
                        frame.setTexture(gpu_frame);
                        gpu_texture_loaded = false;
                    }
                    else
                    {
                        gpu_frame.loadFromImage(buffer[curr_frame]);
                        frame.setTexture(gpu_frame);
                        curr_frame++;
                    }
                }
                else { std::cout << "frame skipping" << '\n'; }
                passedTime = static_cast<int>(clock.restart().asMicroseconds());
            }
            else if (passedTime < VIDEO_FPS - 200)
            {
                if (!gpu_texture_loaded && curr_frame <= FRAMES
                    && curr_frame < ready_frame.load(std::memory_order_acquire))
                {
                    gpu_frame.loadFromImage(buffer[curr_frame]);
                    gpu_texture_loaded = true;
                    curr_frame++;
                    std::cout << "GPU Loaded " << curr_frame << '\n';
                }
                passedTime += static_cast<int>(clock.restart().asMicroseconds());
            }
        }
        GarbageCollector();

        //std::cout << passedTime << '\n';
        /*auto endTime = std::chrono::steady_clock::now();
            std::cout << "Time elapsed - "
                << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << '\n';*/
    }
}

video_sfml::video_sfml(const std::string& path, 
    const unsigned int& framesAmount, const unsigned int& FPS, const sf::RenderWindow& window)
{
	VIDEO_FPS = 1000000 / FPS;
	FRAMES = framesAmount;
	this->path = path;

    gpu_frame.setSmooth(true);
    
    frame.setOrigin(sf::Vector2f(640, 360));
    frame.setScale(sf::Vector2f(window.getSize().x / 1280.0, window.getSize().y / 720.0));
    frame.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

    track.openFromFile("Resource/cutscene/track.wav");

    buffer.resize(299);
}

void video_sfml::Prebuffering(const unsigned int pre_loaded_frames)
{
    if (pre_loaded_frames <= FRAMES)
    {
        for (ready_frame = 0; ready_frame < pre_loaded_frames + 1; ready_frame++)
        {
            if (ready_frame < 10)
            {
                prefix = "000" + std::to_string(ready_frame) + ".png";
            }
            else if (ready_frame < 100)
            {
                prefix = "00" + std::to_string(ready_frame) + ".png";
            }
            else if (ready_frame < 1000)
            {
                prefix = "0" + std::to_string(ready_frame) + ".png";
            }
            buffer[ready_frame].loadFromFile(path + prefix);
            std::cout << "loaded " << ready_frame << std::endl;
        }
    }
    else
    {
        std::cout << "An error has occuried" << '\n';
    }
}

void video_sfml::Start()
{
    std::thread load_thread(&video_sfml::TextureStreaming, this);
    std::thread playingthread(&video_sfml::Play, this);
    
    playingthread.detach();
    load_thread.detach();
}

sf::RenderWindow& video_sfml::VideoShow(sf::RenderWindow& window)
{
    window.draw(frame);
    return window;
}

video_sfml::~video_sfml() {}
