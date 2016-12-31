#include "stdafx.h"
#include "Keyboard2D.h"
#include "Keyboard3D.h"
#include "vld.h"

TEST(PianoKeyboard, MemoryLeaks)
{
	const auto before(VLDGetLeaksCount());
	TCHAR buffer[MAX_PATH] = TEXT("");
	GetCurrentDirectory(ARRAYSIZE(buffer), buffer);
	const auto keyboard2D(new Keyboard2D(nullptr, buffer));
	const auto keyboard3D(new Keyboard3D(nullptr, buffer));

	keyboard2D->ReleaseKeys();
	keyboard3D->ReleaseKeys();
	srand(static_cast<unsigned>(time(nullptr)));
	keyboard2D->UpdateSize(nullptr, static_cast<UINT>(rand()), static_cast<UINT>(rand()));
	keyboard3D->UpdateSize(nullptr, static_cast<UINT>(rand()), static_cast<UINT>(rand()));
	for (auto i(0); i < rand(); ++i)
	{
		if (i >= 21 && i <= 108)
		{
			keyboard2D->PressKey(static_cast<int16_t>(i));
			keyboard3D->PressKey(static_cast<int16_t>(i));
			keyboard2D->AssignFinger(static_cast<int16_t>(i), "12345", i % 2 == 0);
			keyboard3D->AssignFinger(static_cast<int16_t>(i), "12345", i % 2 == 0);
		}
	}
	keyboard2D->Update(nullptr);
	keyboard3D->Update(nullptr);
	keyboard2D->ReleaseKeys();
	keyboard3D->ReleaseKeys();

	delete keyboard2D;
	delete keyboard3D;
	ASSERT_EQ(before, VLDGetLeaksCount());
}