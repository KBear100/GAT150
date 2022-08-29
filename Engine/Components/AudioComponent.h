#pragma once
#include "Framework/Component.h"
#include "Audio/AudioChannel.h"

namespace Bear
{
	class AudioComponent : public Component
	{
	public:
		AudioComponent() = default;
		~AudioComponent();

		CLASS_DECLARATION(AudioComponent)

		void Initialize();
		void Update() override;

		void Play();
		void Stop();

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	public:
		AudioChannel m_channel;

		std::string sound_name;
		bool play_on_start = false;
		float volume = 1.0f;
		float pitch = 1.0f;
		bool loop = false;
	};
}