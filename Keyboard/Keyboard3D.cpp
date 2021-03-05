#include "stdafx.h"
#include "Keyboard3D.h"
#include "Render.h"
#include "DxError.h"

Keyboard3D::Keyboard3D(const HWND hWnd, LPCTSTR path, const bool isVolumeNormalized)
	: IKeyboard(hWnd, path, isVolumeNormalized),
	render_(nullptr),
	path_(path),
	width_(0),
	height_(0)
{
	width_ = static_cast<UINT>(GetSystemMetrics(SM_CXSCREEN));
	height_ = static_cast<UINT>(GetSystemMetrics(SM_CYSCREEN));
}
Keyboard3D::~Keyboard3D()
{
	delete render_;
}

#define RENDER(DO_WHAT) if (render_) try { render_-> ## DO_WHAT ; } catch (const DxError& e) \
	{ MessageBox(hWnd_, e.RusWhat(), TEXT("DirectX Error"), MB_OK | MB_ICONHAND); }

void Keyboard3D::UpdateSize(const UINT width, const UINT height)
{
	width_ = width;
	height_ = height;

	RENDER(Resize(width, height))
else try
	{
		render_ = new Render(hWnd_, width, height, path_.c_str());
	}
	catch (const DxError& e)
	{
		MessageBox(hWnd_, e.RusWhat(), TEXT("DirectX Error"), MB_OK | MB_ICONHAND);
	}
}

void Keyboard3D::ReleaseKeys() const
{
	RENDER(ReleaseAllKeys());
}
void Keyboard3D::AddKey(const int16_t note) const
{
	assert("Note is outside the keyboard" && note >= minNote && note <= maxNote);
	RENDER(PressKey(note - 21));
}
void Keyboard3D::AssignFinger(const int16_t note, const char* fingers, const bool leftHand) const
{
	assert("Note is outside the keyboard" && note >= minNote && note <= maxNote);
	RENDER(AssignFingerNums(note - 21, fingers, leftHand));
}

void Keyboard3D::Draw(const HDC) const
{
	RENDER(Draw());
}

void Keyboard3D::Restore3DPosition() const
{
	if (render_) try
	{
		while (!render_->Restore3DPosition()) Update();
	}
	catch (const DxError& e)
	{
		MessageBox(hWnd_, e.RusWhat(), TEXT("DirectX Error"), MB_OK | MB_ICONHAND);
	}
}
void Keyboard3D::Zoom3D(const int delta) const
{
	if (render_) try
	{
		for (auto i(0); i < abs(delta) * 5; ++i)
		{
			if (!render_->Zoom(delta > 0)) break;
			Update();
		}
	}
	catch (const DxError& e)
	{
		MessageBox(hWnd_, e.RusWhat(), TEXT("DirectX Error"), MB_OK | MB_ICONHAND);
	}
}
void Keyboard3D::Fit3DToWindow() const
{
	if (render_) try
	{
		while (!render_->FitToWindow()) Update();
	}
	catch (const DxError& e)
	{
		MessageBox(hWnd_, e.RusWhat(), TEXT("DirectX Error"), MB_OK | MB_ICONHAND);
	}
}

float Divide(int divisible, UINT divider) { return static_cast<float>(divisible) / static_cast<float>(divider); }
#define UNIT_COORD Divide(x, width_), Divide(y, height_)

#pragma warning(push)
#pragma warning(disable:5045) // Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
void Keyboard3D::Move3DStart(const int x, const int y) const
{
	if (render_) try
	{
		const auto unitX(Divide(x, width_)), unitY(Divide(y, height_));
		// it is screen coordinates when right-click --> context menu is shown:
		if (unitX >= 0 && unitX <= 1 && unitY >= 0 && unitY <= 1) render_->MoveStart(unitX, unitY);
	}
	catch (const DxError& e)
	{
		MessageBox(hWnd_, e.RusWhat(), TEXT("DirectX Error"), MB_OK | MB_ICONHAND);
	}
}
#pragma warning(pop)
void Keyboard3D::Rotate3DStart(const int x, const int y) const
{
	if (render_) try
	{
		render_->RotateStart(UNIT_COORD);
	}
	catch (const DxError& e)
	{
		MessageBox(hWnd_, e.RusWhat(), TEXT("DirectX Error"), MB_OK | MB_ICONHAND);
	}
}
void Keyboard3D::On3DMouseMove(const int x, const int y, const bool move, const bool rotate) const
{
	if (render_) try
	{
		if (move) render_->MoveEnd(UNIT_COORD);
		if (rotate) render_->RotateEnd(UNIT_COORD);
	}
	catch (const DxError& e)
	{
		MessageBox(hWnd_, e.RusWhat(), TEXT("DirectX Error"), MB_OK | MB_ICONHAND);
	}
}