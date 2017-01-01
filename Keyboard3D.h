#pragma once
#include "IKeyboard.h"

class Keyboard3D : public IKeyboard
{
	Keyboard3D() = delete;
public:
	explicit Keyboard3D(HWND, float cameraX, float cameraY, float cameraZ, LPCTSTR path);
	virtual ~Keyboard3D() override final;

	virtual void UpdateSize(HWND, UINT width, UINT height) override final;
	virtual void ReleaseKeys() const override final;
	virtual void AssignFinger(int16_t note, const char* fingers, bool leftHand) const override final;
private:
	const class Render* render_;
	const float cameraX_, cameraY_, cameraZ_;
	const std::wstring path_;

	virtual void AddKey(int16_t note) const override final;
	virtual void Draw(HDC) const override final;

	Keyboard3D(const Keyboard3D&) = delete;
	Keyboard3D(const Keyboard3D&&) = delete;
	Keyboard3D& operator=(const Keyboard3D&) = delete;
	Keyboard3D&& operator=(const Keyboard3D&&) = delete;
};