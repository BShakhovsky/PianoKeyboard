#include "stdafx.h"
#include "Keyboard2D_pimpl.h"
#include "NoteNames.h"
#include "PianoFingering\BlackWhiteKeys.h"
#include "IKeyboard.h"

using namespace std;
using namespace boost;

#pragma warning(push)
#pragma warning(disable:26495) // leftGap uninitialized
struct KeyboardData : private noncopyable
{
	static constexpr int nOctaves = 7,
		nWhiteKeys = nOctaves * 7 + 2 + 1;

	int leftGap, bottomGap,
		width, height, keyWidth, keyHeight;
	
	RECT rect;
	HDC hdcMem;
	HBITMAP hBitmap;
	HBRUSH hBrushWhite, hBrushBlack;

	vector<int16_t> pressedBlackKeys;
	vector<tuple<int16_t, wstring, bool>> fingerNumbers;
};
#pragma warning(pop)
Keyboard2D_pimpl::Keyboard2D_pimpl()
	: data_(make_unique<KeyboardData>())
{
	data_->leftGap = 0;
	data_->bottomGap = 0;

	data_->width = 0;
	data_->height = 0;
	data_->keyWidth = 0;
	data_->keyHeight = 0;

	ZeroMemory(&data_->rect, sizeof data_->rect);

	data_->hdcMem = nullptr;
	data_->hBitmap = nullptr;

	data_->hBrushWhite = CreateHatchBrush(HS_DIAGCROSS, 0x90'90'90);
	data_->hBrushBlack = CreateHatchBrush(HS_DIAGCROSS, 0xFF'FF'FF);
	
	data_->pressedBlackKeys = vector<int16_t>();
	data_->fingerNumbers = vector<tuple<int16_t, wstring, bool>>();
}
#pragma warning(push)
#pragma warning(disable:4711)
Keyboard2D_pimpl::~Keyboard2D_pimpl()
{
	if (!data_->hdcMem)		DeleteDC(data_->hdcMem);
	if (!data_->hBitmap)	DeleteBitmap(data_->hBitmap);
	DeleteBrush(data_->hBrushWhite);
	DeleteBrush(data_->hBrushBlack);
}
#pragma warning(pop)

void Keyboard2D_pimpl::UpdateSize(const HWND hWnd, const int width, const int height)
{
	const auto hdc(GetDC(hWnd));
	data_->hdcMem = CreateCompatibleDC(hdc);

	data_->width = width;
	data_->height = height;
	data_->keyWidth = data_->width / data_->nWhiteKeys;
	data_->keyHeight = data_->keyWidth * 5;
	data_->leftGap = (data_->width - data_->keyWidth * data_->nWhiteKeys) / 2;

	DeleteBitmap(data_->hBitmap);
	data_->hBitmap = CreateCompatibleBitmap(hdc, data_->width, data_->height);
	ReleaseDC(hWnd, hdc);
	SelectBitmap(data_->hdcMem, data_->hBitmap);

	RECT rect{ 0 };
	GetClientRect(hWnd, &rect);
	FillRect(data_->hdcMem, &rect, GetStockBrush(WHITE_BRUSH));

	SetBkMode(data_->hdcMem, TRANSPARENT);
}

inline int16_t CalcWhiteKeyIndex(int16_t note)
{
	auto noteIndex(NoteNames::GetNoteNumber(note));
	return static_cast<int16_t>((noteIndex < 5 ? noteIndex / 2 : (noteIndex + 1) / 2)
		+ (NoteNames::GetOctaveNumber(note) - 2) * 7 + 2);
}
inline int16_t CalcBlackKeyIndex(int16_t note)
{
	return static_cast<int16_t>(NoteNames::GetNoteNumber(note) / 2
		+ (NoteNames::GetOctaveNumber(note) - 2) * 7 + 3);
}
inline void Keyboard2D_pimpl::GetWhiteKeyPosition(const int16_t keyIndex)
{
	data_->rect.left	= data_->leftGap + keyIndex * data_->keyWidth;
	data_->rect.right	= data_->leftGap + (keyIndex + 1) * data_->keyWidth;

	data_->rect.top		= data_->height - data_->bottomGap - data_->keyHeight;
	data_->rect.bottom	= data_->height - data_->bottomGap;
}
inline void Keyboard2D_pimpl::GetBlackKeyPosition(const int16_t keyIndex)
{
	data_->rect.left	= data_->leftGap + keyIndex * data_->keyWidth - data_->keyWidth / 3;
	data_->rect.right	= data_->leftGap + keyIndex * data_->keyWidth + data_->keyWidth / 3;

	data_->rect.top		= 0;
//	data_->rect.top		= data_->height - data_->bottomGap - data_->keyHeight - data_->keyHeight / 3;
	data_->rect.bottom	= data_->height - data_->bottomGap - data_->keyHeight + data_->keyHeight / 2;
}

void Keyboard2D_pimpl::PressWhiteKey(const int16_t note)
{
	GetWhiteKeyPosition(CalcWhiteKeyIndex(note));

	SetBkColor(data_->hdcMem, RGB(0xFF, 0xFF, 0xFF));
	FillRect(data_->hdcMem, &data_->rect, data_->hBrushWhite);

	DrawEdge(data_->hdcMem, &data_->rect, EDGE_SUNKEN, BF_RECT);
}
inline void Keyboard2D_pimpl::PressBlackKey(const int16_t note)
{
	GetBlackKeyPosition(CalcBlackKeyIndex(note));

	SetBkColor(data_->hdcMem, 0);
	FillRect(data_->hdcMem, &data_->rect, data_->hBrushBlack);

	DrawEdge(data_->hdcMem, &data_->rect, EDGE_SUNKEN, BF_RECT);
}
#pragma warning(push)
#pragma warning(disable:4711)
void Keyboard2D_pimpl::PressKey(const int16_t note)
{
	assert("Note is outside the keyboard" && note >= IKeyboard::minNote && note <= IKeyboard::maxNote);

	if (BlackWhiteKeys::IsWhite(note))
		PressWhiteKey(note);
	else
		data_->pressedBlackKeys.push_back(note);
}
#pragma warning(pop)

inline void Keyboard2D_pimpl::DrawReleasedWhiteKey(const int16_t keyIndex)
{
	GetWhiteKeyPosition(keyIndex);
	FillRect(data_->hdcMem, &data_->rect, GetStockBrush(WHITE_BRUSH));
	DrawEdge(data_->hdcMem, &data_->rect, EDGE_RAISED, BF_RECT);
}
inline void Keyboard2D_pimpl::DrawReleasedBlackKey(const int16_t keyIndex)
{
	GetBlackKeyPosition(keyIndex);
	FillRect(data_->hdcMem, &data_->rect, GetStockBrush(BLACK_BRUSH));
	DrawEdge(data_->hdcMem, &data_->rect, EDGE_RAISED, BF_RECT);
}
void Keyboard2D_pimpl::ReleaseWhiteKeys()
{
	for (int16_t i(0); i < data_->nWhiteKeys; ++i)
		DrawReleasedWhiteKey(i);
}
void Keyboard2D_pimpl::ReleaseBlackKeys()
{
	DrawReleasedBlackKey(1);
	for (int16_t i(0); i < data_->nOctaves; ++i)
	{
		for (int16_t j(0); j < 2; ++j) DrawReleasedBlackKey(3 + i * 7 + j);
		for (int16_t j(0); j < 3; ++j) DrawReleasedBlackKey(6 + i * 7 + j);
	}
}

void Keyboard2D_pimpl::AssignFinger(const int16_t note, const char* fingers, const bool leftHand)
{
	assert("Note is outside the keyboard" && note >= IKeyboard::minNote && note <= IKeyboard::maxNote);

	auto text(lexical_cast<wstring>(fingers));
	const auto len(text.length());
	for (size_t i(0); i < len - 1; ++i) text.insert(i * 2 + 1, TEXT("\n"), 1);
	data_->fingerNumbers.emplace_back(make_tuple(note, text, leftHand));
}
inline void Keyboard2D_pimpl::DrawFinger(const wstring& fingers, const bool leftHand)
{
	data_->rect.top = (data_->rect.top + data_->rect.bottom) / 2;
	SetTextColor(data_->hdcMem, leftHand ? RGB(0, 0xB0, 0xFF) : RGB(0xFF, 0, 0));
	DrawText(data_->hdcMem, fingers.c_str(), static_cast<int>(fingers.length()),
		&data_->rect, DT_CENTER);
}

void Keyboard2D_pimpl::Draw(const HDC hdc)
{
	ReleaseBlackKeys();
	for (const auto& blackNote : data_->pressedBlackKeys)
		PressBlackKey(blackNote);

	for (const auto& finger : data_->fingerNumbers)
	{
		int16_t note(0);
		wstring fingers;
		bool leftHand(false);
		tie(note, fingers, leftHand) = finger;

		if (BlackWhiteKeys::IsWhite(note))
			GetWhiteKeyPosition(CalcWhiteKeyIndex(note));
		else
			GetBlackKeyPosition(CalcBlackKeyIndex(note));
		DrawFinger(fingers, leftHand);
	}

	data_->pressedBlackKeys.clear();
	data_->fingerNumbers.clear();

	BitBlt(hdc, 0, 0, data_->width, data_->height, data_->hdcMem, 0, 0, SRCCOPY);
}