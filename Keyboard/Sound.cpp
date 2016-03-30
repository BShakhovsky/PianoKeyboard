#include "stdafx.h"
#include "Sound.h"
#include "SoundError.h"

using namespace std;
using namespace DirectX;

Sound::Sound(LPCTSTR path)
{
	CoInitialize(nullptr);
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

	for (auto i(0); i < 6; ++i) chords_.push(vector<shared_ptr<SoundEffectInstance>>());
}

Sound::~Sound()
{
	if (audio_) audio_->Suspend();
}

void Sound::AddNote(int16_t note)
{
	static const auto NOTE_MIN(21), NOTE_MAX(108);
	assert("Note is outside the keyboard" && note >= NOTE_MIN && note <= NOTE_MAX);
	if (note < NOTE_MIN) note = NOTE_MIN;
	if (note > NOTE_MAX) note = NOTE_MAX;
	chords_.back().push_back(shared_ptr<SoundEffectInstance>(
		notes_->CreateInstance(note - NOTE_MIN).release()));
}

void Sound::Play()
{
	for (const auto& note : chords_.back()) note->Play();
	chords_.pop();
	chords_.push(vector<shared_ptr<SoundEffectInstance>>());
}