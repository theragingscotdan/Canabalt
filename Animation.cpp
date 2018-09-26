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
	// only process the animation if it is playing
	if (m_playing)
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
												
				//should we loop
				if (m_loop)
				{
					// Wrap around to beginning
					m_currentFrame = 0;
				}
				else
				{
					// we should not loop

					// set out frame as the last in the list
					m_currentFrame = m_frames.size() - 1;

					// stop playback
					m_playing = false;
				}
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
}

void Animation::Play()
{
	// only start playing and set next frame time IF playback speed is nonzero
	// (avoid a divide by zero error)
	if (m_sprite)
	{
		m_sprite->setTexture(*m_frames[m_currentFrame]);
	}
	if (m_playBackSpeed != 0)
	{

		m_playing = true;

		// determine time for next frame change
		// convert frames per seconds to seconds per frame
		float timeToChange = 1.0 / m_playBackSpeed;
		m_nextFrameChange = sf::seconds(timeToChange);
	}
}

void Animation::Pause()
{
	// stop playback, keeping current frame as is
	m_playing = false;

}

void Animation::Stop()
{
	// stop playback AND reset to first frame
	m_playing = false;
	m_currentFrame = 0;

}

bool Animation::IsPlaying()
{
	// tell the calling code if we are currently playing
	return m_playing;
}


void Animation::AddFrame(sf::Texture& _newFrame)
{
	m_frames.push_back(&_newFrame);
}

void Animation::SetSprite(sf::Sprite&_sprite)
{
	m_sprite = &_sprite;
}

void Animation::SetPlayBackSpeed(float _framesPerSecond)
{
	m_playBackSpeed = _framesPerSecond;

	// if the playback is zero
	// pause to protect from divide by zero error

	if (m_playBackSpeed == 0)
		Pause();
	}


void Animation::SetLoop(bool _loop)
{
	m_loop = _loop;
}
