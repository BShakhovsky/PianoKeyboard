#pragma once
#pragma comment(lib, "Keyboard.lib")

class IKeyboard abstract
{
	IKeyboard() = delete;
protected:
	explicit IKeyboard(HWND, LPCTSTR path);
	virtual ~IKeyboard();
public:
	virtual void UpdateSize(HWND, UINT width, UINT height) = 0;

	void PressKey(int16_t note);
	virtual void ReleaseKeys() const = 0;
	virtual void AssignFinger(int16_t note, const char* fingers, bool leftHand = false) const = 0;

	void Update(HDC hDC = nullptr) const;
private:
	virtual void AddKey(int16_t note) const = 0;
	virtual void Draw(HDC) const = 0;

	class Sound* sound_;
};

#include "Keyboard2D.h"
#include "Keyboard3D.h"