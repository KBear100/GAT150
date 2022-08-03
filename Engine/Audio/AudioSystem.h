#pragma once
#include <map>
#include <string>

namespace FMOD
{
	class System;
	class Sound;
}

namespace Bear
{
	class AudioSystem
	{
	public:
		AudioSystem() = default;
		~AudioSystem() = default;

		void Initialize();
		void ShutDown();

		void Update();

		void AddAudio(const std::string& name, const std::string& filename);
		void PlayAudio(const std::string& name, bool loop = false);

	private:
		FMOD::System* m_fmodSystem;
		std::map<std::string, FMOD::Sound*> m_sounds;
	};
}