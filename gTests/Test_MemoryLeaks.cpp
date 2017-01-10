#include "stdafx.h"
#include "Keyboard2D.h"
#include "Keyboard3D.h"
#include "vld.h"

TEST(PianoKeyboard, DISABLED_MemoryLeaks)
{
	TCHAR buffer[MAX_PATH] = TEXT("");
	GetCurrentDirectory(ARRAYSIZE(buffer), buffer);
	const auto before(VLDGetLeaksCount());
	const auto keyboard2D(new Keyboard2D(nullptr, buffer));
	const auto keyboard3D(new Keyboard3D(nullptr, 26.0f, 25.0f, 30.0f, buffer));

	keyboard2D->ReleaseKeys();
	keyboard3D->ReleaseKeys();
	srand(static_cast<unsigned>(time(nullptr)));
	keyboard2D->UpdateSize(nullptr, static_cast<UINT>(rand()), static_cast<UINT>(rand()));
	keyboard3D->UpdateSize(nullptr, static_cast<UINT>(rand()), static_cast<UINT>(rand()));

	for (int16_t i(0); i < static_cast<int16_t>(rand()); ++i)
		if (i >= 21 && i <= 108)
		{
			keyboard2D->PressKey(i, static_cast<float>(rand()) / RAND_MAX);
			keyboard3D->PressKey(i, static_cast<float>(rand()) / RAND_MAX);
			keyboard2D->AssignFinger(i, "12345", i % 2 == 0);
			keyboard3D->AssignFinger(i, "12345", i % 2 == 0);
		}

	keyboard2D->Update(nullptr);
	keyboard3D->Update(nullptr);
	keyboard2D->ReleaseKeys();
	keyboard3D->ReleaseKeys();

	delete keyboard3D;
	delete keyboard2D;
	ASSERT_EQ(before, VLDGetLeaksCount());
}