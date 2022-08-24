#pragma once

namespace FMOD
{
	class Channel;
}

namespace Bear
{
	class AudioChannel
	{
	public:
		AudioChannel() = default;
		AudioChannel(FMOD::Channel* channel) : m_channel{ channel } {}

		bool IsPlaying();
		void Stop();

		void SetPitch(float pitch);
		float GetPitch();
		
		void SetVolume(float volume);
		float GetVolume();

	private:
		FMOD::Channel* m_channel = nullptr;
	};
}