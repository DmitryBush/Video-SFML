#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <future>
#include <thread>

class video_sfml
{
private:
	unsigned int VIDEO_FPS;
	unsigned int FRAMES;

	std::atomic <unsigned int> ready_frame = 0;
	unsigned int curr_frame = 0;
	unsigned int frame_mem_cleaner = 0;
	std::mutex lock;

	float passedTime = 0;

	std::string path;
	std::string prefix;


	sf::Image buffer[300];
	sf::Texture gpu_frame;
	bool gpu_texture_loaded = false;

	sf::Sprite frame;
	sf::Clock clock;

	sf::Music track;

	void TextureStreaming();
	void GarbageCollector();
	void Play(bool sync);
public:
	video_sfml(const std::string& path, const unsigned int& framesAmount, const unsigned int& FPS,
		const sf::RenderWindow& window);
	void Prebuffering(const unsigned int pre_loaded_frames);
	void StartStreaming();
	void Start();

	sf::RenderWindow& VideoShow(sf::RenderWindow& window);

	~video_sfml();
};