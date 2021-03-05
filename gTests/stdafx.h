#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#pragma warning(push, 3)
#	include <Windows.h>
#pragma warning(pop)

#pragma warning(disable:4626 4710)
#pragma warning(push, 1)
#pragma warning(disable:4365 4514 4571 4623 4625 4711 4774 4820 5026 5027)
#pragma warning(disable:26495 26812 28182)
#	include <gtest\gtest.h>
#	ifdef _DEBUG
#		pragma comment(lib, "gtestd")
#		pragma comment(lib, "gtest_maind")
#	else
#		pragma comment(lib, "gtest")
#		pragma comment(lib, "gtest_main")
#	endif
#pragma warning(pop)

#	pragma comment(lib, "PianoFingering")

#pragma warning(disable:4571)	// SEH are no longer caught