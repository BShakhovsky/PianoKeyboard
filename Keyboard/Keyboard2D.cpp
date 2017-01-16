#include "stdafx.h"
#include "Keyboard2D.h"
#include "Keyboard2D_pimpl.h"

Keyboard2D::Keyboard2D(const HWND hWnd, LPCTSTR path, const bool isVolumeNormalized)
	: IKeyboard(hWnd, path, isVolumeNormalized),
	pimpl_(new Keyboard2D_pimpl)
{}

#pragma warning(push)
#pragma warning(disable:4711)	// automatic inline expansion
Keyboard2D::~Keyboard2D()
{
	delete pimpl_;
}
#pragma warning(pop)

void Keyboard2D::UpdateSize(const HWND hWnd, const UINT width, const UINT height)
{
	pimpl_->UpdateSize(hWnd, static_cast<int>(width), static_cast<int>(height));
}

void Keyboard2D::AddKey(const int16_t note) const
{
	assert("Note is outside the keyboard" && note >= minNote && note <= maxNote);
	pimpl_->PressKey(note);
}
void Keyboard2D::ReleaseKeys() const
{
	pimpl_->ReleaseWhiteKeys();
}

void Keyboard2D::AssignFinger(const int16_t note, const char* fingers, const bool leftHand) const
{
	assert("Note is outside the keyboard" && note >= minNote && note <= maxNote);
	pimpl_->AssignFinger(note, fingers, leftHand);
}

void Keyboard2D::Draw(const HDC hdc) const
{
	pimpl_->Draw(hdc);
}