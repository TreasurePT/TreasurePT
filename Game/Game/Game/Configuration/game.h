#pragma once
#include "stdafx.h"
#include "global.h"

#pragma region Level_Definition

#define MAXIMUM_LEVEL_SERVER TRUE

#if MAXIMUM_LEVEL_SERVER == FALSE

#define LEVEL_CAP 100

#define LEVEL_CONSTANT 100

#define LEVEL_MULTIPLIER 1.1f

#endif

#pragma endregion