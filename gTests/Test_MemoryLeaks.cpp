#include "stdafx.h"
#include "Keyboard.h"
#include "vld.h"

TEST(PianoKeyboard, MemoryLeads)
{
	const auto before(VLDGetLeaksCount());
	const auto keyboard(new Keyboard);
	
	keyboard->ReleaseWhiteKeys();
	srand(static_cast<unsigned>(time(nullptr)));
	keyboard->UpdateSize(nullptr, rand(), rand());
	for (auto i(0); i < rand(); ++i)
	{
		keyboard->PressKey(static_cast<int16_t>(i));
		keyboard->AssignFinger(static_cast<int16_t>(i), "12345", i % 2 == 0);
	}
	keyboard->Draw(nullptr);
	keyboard->ReleaseWhiteKeys();

	delete keyboard;

	ASSERT_EQ(before, VLDGetLeaksCount());
}