#pragma once
#include "IKeyboard.h"
class Keyboard3D : public IKeyboard
{
	Keyboard3D() = delete;
public:
	explicit Keyboard3D(HWND, LPCTSTR path, bool isVolumeNormalized = false);
	virtual ~Keyboard3D() override final;

	virtual void UpdateSize(UINT width, UINT height) override final;
	virtual void ReleaseKeys() const override final;
	virtual void AssignFinger(int16_t note, const char* fingers, bool leftHand) const override final;

	virtual void Restore3DPosition() const override final;
	virtual void Zoom3D(int delta) const override final;
	virtual void Fit3DToWindow() const override final;

	virtual void Move3DStart(int x, int y) const override final;
	virtual void Rotate3DStart(int x, int y) const override final;
	virtual void On3DMouseMove(int x, int y, bool move, bool rotate) const override final;
private:
	const class Render* render_;
	const std::wstring path_;
	UINT width_, height_;

	virtual void AddKey(int16_t note) const override final;
	virtual void Draw(HDC) const override final;

	Keyboard3D(const Keyboard3D&) = delete;
	Keyboard3D(const Keyboard3D&&) = delete;
	Keyboard3D& operator=(const Keyboard3D&) = delete;
	Keyboard3D&& operator=(const Keyboard3D&&) = delete;
};