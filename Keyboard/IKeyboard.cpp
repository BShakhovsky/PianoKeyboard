#include "stdafx.h"
#include "IKeyboard.h"
#include "Sound.h"
#include "SoundError.h"

using std::pair;

IKeyboard::IKeyboard(const HWND hWnd, LPCTSTR path, const bool isVolumeNormalized)
	: hWnd_(hWnd),
	sound_(nullptr)
{
	try
	{
		sound_ = new Sound(path, isVolumeNormalized);
	}
	catch (const SoundError& e)
	{
		MessageBox(hWnd, e.RusWhat(), TEXT("Sound Error"), MB_OK | MB_ICONHAND);
	}

	NormalizeVolume(isVolumeNormalized);
}

inline IKeyboard::~IKeyboard()
{
	if (sound_) delete sound_;
}

void IKeyboard::PressKey(const pair<int16_t, float>& note_volume)
{
	auto note(note_volume.first);
	if (note < minNote) note = minNote;
	else if (note > maxNote) note = maxNote;

	AddKey(note);
	if (sound_) sound_->AddNote(note, note_volume.second);
}

void IKeyboard::Update(const HDC hDC) const
{
	Draw(hDC);
	if (sound_) sound_->Play();
}

inline void IKeyboard::NormalizeVolume(const bool normalize) const
{
	if (sound_) sound_->NormalizeVolume(normalize);
}