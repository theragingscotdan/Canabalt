#pragma once
// library includes
#include <vector>
#include <SFML/Graphics.hpp>

class Animation
{

public:

	Animation();

	void Update(sf::Time _frameTime);
	
	void Play();
	void Pause();
	void Stop();

	bool IsPlaying();

	void AddFrame(sf::Texture& _newFrame);
	void SetSprite(sf::Sprite& _sprite);
	void SetPlayBackSpeed(float _framesPerSecond);
	void SetLoop(bool _loop);

	
private:

	// settings
	int m_currentFrame;
	sf::Sprite* m_sprite;
	float m_playBackSpeed;
	bool m_loop;

	// state
	bool m_playing;
	std::vector<sf::Texture*> m_frames;
	sf::Time m_nextFrameChange;




};