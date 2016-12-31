#include "stdafx.h"
#include "IKeyboard.h"
#include "Sound.h"
#include "SoundError.h"

IKeyboard::IKeyboard(const HWND hWnd, LPCTSTR path)
	: sound_(nullptr)
{
	try
	{
		sound_ = new Sound(path);
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

void IKeyboard::PressKey(const int16_t note)
{
	AddKey(note);
	if (sound_) sound_->AddNote(note);
}

void IKeyboard::Update(const HDC hDC) const
{
	Draw(hDC);
	if (sound_) sound_->Play();
}