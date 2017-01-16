#include "stdafx.h"
#include "Sound.h"
#include "SoundError.h"
#include "IKeyboard.h"

using namespace std;
using namespace DirectX;

Sound::Sound(LPCTSTR path, const bool isVolumeNormalized)
	: isVolumeNormalized_(isVolumeNormalized)
{
	const auto hResult(CoInitialize(nullptr));
	THROW_IF_FAILED(SoundError, hResult,
		"Could not initialize audio device.\nThere will be no sound until you restart the program");

	audio_ = make_unique<AudioEngine>(AudioEngine_Default
#ifdef _DEBUG
		| AudioEngine_Debug
#endif
		);
	if (!audio_->IsAudioDevicePresent())
		throw SoundError("Could not find audio device.\n"
			"There will be no sound until you restart the program");

	try
	{
		notes_ = make_unique<WaveBank>(audio_.get(), (wstring(path) + TEXT("\\Sounds.xwb")).c_str());
	}
	catch (const exception& e)
	{
		if (string(e.what()) == "WaveBank")
		{
			wstring pathW(path);
			string pathA(pathW.cbegin(), pathW.cend());
			throw SoundError(("Could not find the following file:\n'" + pathA + "\\Sounds.xwb'\n"
				+ "There will be no sound until you put the file back and then restart the program."
				).c_str());
		}
		else throw;
	}

	for (size_t i(0); i < chordsSize_; ++i)
		chords_.push(vector<shared_ptr<SoundEffectInstance>>());
}

#pragma warning(push)
#pragma warning(disable:4711)
Sound::~Sound()
{
	if (audio_) audio_->Suspend();
}
#pragma warning(pop)

void Sound::AddNote(const int16_t note, const float volume)
{
	assert("Note is outside the keyboard" && note >= IKeyboard::minNote && note <= IKeyboard::maxNote);
	chords_.back().push_back(shared_ptr<SoundEffectInstance>(
		notes_->CreateInstance(note - IKeyboard::minNote).release()));

	assert("Volume must be between 0 and 1" && volume >= 0 && volume <= 1);
	if (!isVolumeNormalized_) chords_.back().back()->SetVolume(volume);
}

void Sound::Play()
{
	for (const auto& note : chords_.back()) note->Play();

	// During 3D-mode, sound is like with pressed damper (sustain) pedal
	// (however, if main window menu item is selected, then no, everything is Ok)
	// Probably, it is compiler optimization, and chords_.size() == 1 instead of 6 for some reason
	// Fix it for Release (for both 2D- and 3D-modes though):
#ifdef NDEBUG
	if (chords_.size() > chordsSize_) // works only with the same number in both conditionals
#endif
		chords_.pop();
#ifdef NDEBUG
	if (chords_.size() < chordsSize_)
#endif
		chords_.push(vector<shared_ptr<SoundEffectInstance>>());
}