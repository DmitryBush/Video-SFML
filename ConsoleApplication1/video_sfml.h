#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class video_sfml
{
private:
	unsigned int VIDEO_FPS;
	unsigned int FRAMES;
	unsigned int ready_frame = 0;
	unsigned int curr_frame = 0;
	unsigned int frame_mem_cleaner = 0;

	unsigned int passedTime = 0;

	std::string path;
	std::string prefix;


	sf::Image mov[300];
	sf::Texture image;
	sf::Sprite a;

	void TextureStreaming();
	void GarbageCollector();
	sf::Sprite Play();
public:
	video_sfml(const std::string& path, const unsigned int& framesAmount, const unsigned int& FPS);
	void Prebuffering(const unsigned int pre_loaded_frames);

	sf::RenderWindow& VideoShow(sf::RenderWindow& window);

	~video_sfml();
};