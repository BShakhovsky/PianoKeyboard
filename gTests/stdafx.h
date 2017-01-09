#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#pragma warning(push, 3)
#	include <Windows.h>
#pragma warning(pop)

#pragma warning(disable:4710)
#pragma warning(push, 1)
#pragma warning(disable:4711)
#	include <gtest\gtest.h>
#	ifdef _DEBUG
#		pragma comment(lib, "gtestd")
#		pragma comment(lib, "gtest_main-mdd")
#	else
#		pragma comment(lib, "gtest")
#		pragma comment(lib, "gtest_main")
#	endif
#pragma warning(pop)

#	pragma comment(lib, "PianoFingering")

#pragma warning(disable:4571)	// SEH are no longer caught