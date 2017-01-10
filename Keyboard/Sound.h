#pragma once

class Sound : boost::noncopyable
{
	Sound() = delete;
public:
	explicit Sound(LPCTSTR path, bool isVolumeNormalized);
	~Sound();

	void AddNote(int16_t note, float volume);
	void Play();

#pragma warning(push)
#pragma warning(disable:4514)	// unreferenced inline function has been removed
	void NormalizeVolume(bool normalize = true)
	{
		isVolumeNormalized_ = normalize;
	}
#pragma warning(pop)

private:
	std::unique_ptr<DirectX::AudioEngine> audio_;
	std::unique_ptr<DirectX::WaveBank> notes_;
	std::queue<std::vector<std::shared_ptr<DirectX::SoundEffectInstance>>> chords_;
	static constexpr size_t chordsSize_ = 5;

	bool isVolumeNormalized_;
	const BYTE padding_[3] = { '\0' };
};