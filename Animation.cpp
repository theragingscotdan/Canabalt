// project includes
#include "Animation.h"

Animation::Animation()
	: m_frames ()
	, m_sprite (nullptr)
	, m_playBackSpeed (15.0f)
	, m_loop (false)
	, m_playing (false)
	, m_nextFrameChange ()
	, m_currentFrame (0)

{

}

void Animation::Update(sf::Time _frameTime)
{
	// is it time to change to a new frame
	m_nextFrameChange -= _frameTime;
	if (m_nextFrameChange.asSeconds() <= 0)
	{
		// it's time to change the frame

		// change ot the next frame
		++m_currentFrame;

		// did we reach the end?
		if (m_currentFrame >= m_frames.size())
		{
			// we did reach the end!

			// TODO: What if no loop?

			// Wrap around to beginning
			m_currentFrame = 0;
		}

		// update sprite's texture to match new frame
		// does our sprite exist

		if (m_sprite) // is not = 0 aka null aka nullptrl
		{
			m_sprite->setTexture(*m_frames[m_currentFrame]);
		}

		// determine time for next frame change
		// convert frames per seconds to seconds per frame
		float timeToChange = 1.0f / m_playBackSpeed;
		m_nextFrameChange = sf::seconds(timeToChange);
	}
}

void Animation::AddFrame(sf::Texture& _newFrame)
{
	m_frames.push_back(&_newFrame);
}

void Animation::SetSprite(sf::Sprite&_sprite)
{
	m_sprite = &_sprite;
}