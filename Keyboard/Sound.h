#pragma once

class Sound : boost::noncopyable
{
	Sound() = delete;
public:
	explicit Sound(LPCTSTR path);
	~Sound();

	void AddNote(int16_t note);
	void Play();
private:
	std::unique_ptr<DirectX::AudioEngine> audio_;
	std::unique_ptr<DirectX::WaveBank> notes_;
	std::queue<std::vector<std::shared_ptr<DirectX::SoundEffectInstance>>> chords_;
};