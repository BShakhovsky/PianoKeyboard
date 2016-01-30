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
#pragma warning(pop)
#pragma warning(disable:4571)	// SEH are no longer caught