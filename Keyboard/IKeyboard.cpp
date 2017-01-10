#include "stdafx.h"
#include "IKeyboard.h"
#include "Sound.h"
#include "SoundError.h"

Sound* IKeyboard::sound_ = nullptr;

IKeyboard::IKeyboard(const HWND hWnd, LPCTSTR path, const bool isVolumeNormalized)
{
	try
	{
		sound_ = new Sound(path, isVolumeNormalized);
	}
	catch (const SoundError& e)
	{
		MessageBoxA(hWnd, e.what(), "Sound Error", MB_OK | MB_ICONASTERISK);
	}
}

inline IKeyboard::~IKeyboard()
{
	if (sound_) delete sound_;
}

void IKeyboard::PressKey(const int16_t note, const float volume)
{
	AddKey(note);
	if (sound_) sound_->AddNote(note, volume);
}

void IKeyboard::Update(const HDC hDC) const
{
	Draw(hDC);
	if (sound_) sound_->Play();
}

void IKeyboard::NormalizeVolume(const bool normalize) const
{
	sound_->NormalizeVolume(normalize);
}