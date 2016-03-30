#include "stdafx.h"
#include "Keyboard2D.h"
#include "Keyboard2D_pimpl.h"

Keyboard2D::Keyboard2D(const HWND hWnd, LPCTSTR path)
	: IKeyboard(hWnd, path),
	pimpl_(new Keyboard2D_pimpl)
{}

#pragma warning(push)
#pragma warning(disable:4711)	// automatic inline expansion
Keyboard2D::~Keyboard2D()
{
	delete pimpl_;
}
#pragma warning(pop)

void Keyboard2D::UpdateSize(const HWND hWnd, const UINT width, const UINT height) const
{
	pimpl_->UpdateSize(hWnd, width, height);
}

void Keyboard2D::AddKey(const int16_t note) const
{
	pimpl_->PressKey(note);
}
void Keyboard2D::ReleaseWhiteKeys() const
{
	pimpl_->ReleaseWhiteKeys();
}

void Keyboard2D::AssignFinger(const int16_t note, const char* fingers, const bool leftHand) const
{
	pimpl_->AssignFinger(note, fingers, leftHand);
}

void Keyboard2D::Draw(const HDC hdc) const
{
	pimpl_->Draw(hdc);
}