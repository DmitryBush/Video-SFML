#include "video_sfml.h"

sf::Clock clock;

void video_sfml::TextureStreaming()
{
    if (ready_frame != FRAMES)
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
}

void video_sfml::GarbageCollector()
{
    if (curr_frame > frame_mem_cleaner && frame_mem_cleaner != FRAMES)
    {
        mov[frame_mem_cleaner].~Image();
        frame_mem_cleaner++;
    }
}

sf::Sprite video_sfml::Play()
{
    TextureStreaming();
    if (passedTime >= VIDEO_FPS && curr_frame != FRAMES)
    {
        passedTime = static_cast<int>(clock.restart().asMicroseconds());
        if (curr_frame <= ready_frame)
        {
            image.loadFromImage(mov[curr_frame]);
            a.setTexture(image);
            curr_frame++;
            return a;
        }
        else { std::cout << "frame skipping" << '\n'; return a; }
    }
    else if (passedTime < VIDEO_FPS) 
    {
        passedTime += static_cast<int>(clock.restart().asMicroseconds()); return a;
    }
}

video_sfml::video_sfml(const std::string& path, const unsigned int& framesAmount, const unsigned int& FPS)
{
	VIDEO_FPS = 1000000 / FPS;
	FRAMES = framesAmount;
	this->path = path;
}

void video_sfml::Prebuffering(const unsigned int pre_loaded_frames)
{
    if (pre_loaded_frames < FRAMES)
    {
        for (ready_frame = 0; ready_frame < pre_loaded_frames; ready_frame++)
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
            mov[ready_frame].loadFromFile(path + prefix);
            std::cout << "loaded" << ready_frame << std::endl;
        }
    }
    else
    {
        std::cout << "An error has occuried" << '\n';
    }
}

sf::RenderWindow& video_sfml::VideoShow(sf::RenderWindow& window)
{
    window.clear();
    window.draw(Play());
    return window;
}

video_sfml::~video_sfml() {}
