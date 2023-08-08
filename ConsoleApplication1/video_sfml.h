#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <future>
#include <thread>

class video_sfml
{
private:
	unsigned int VIDEO_FPS;
	unsigned int FRAMES;

	unsigned int ready_frame = 0;
	unsigned int curr_frame = 0;
	unsigned int frame_mem_cleaner = 0;

	float passedTime = 0;

	std::string path;
	std::string prefix;


	sf::Image buffer[300];
	sf::Texture gpu_frame;
	bool gpu_texture_loaded = false;

	sf::Sprite frame;
	sf::Clock clock;

	

	void TextureStreaming();
	void GarbageCollector();
	sf::Sprite Play();
public:
	video_sfml(const std::string& path, const unsigned int& framesAmount, const unsigned int& FPS,
		const sf::RenderWindow& window);
	void Prebuffering(const unsigned int pre_loaded_frames);
	void StartStreaming();

	sf::RenderWindow& VideoShow(sf::RenderWindow& window);

	~video_sfml();
};