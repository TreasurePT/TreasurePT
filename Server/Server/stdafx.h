#pragma once

#define WIN32_LEAN_AND_MEAN
#include <SDKDDKVer.h>
#include <windows.h>
#include <memory>
#include <strsafe.h>
#include <cctype>
#include <vector>

//Definições

#define LEVEL_CAP 100
#define LEVEL_EXP_BASE 100
#define LEVEL_MULTIPLIER 1.1f

#define PDATA 0x08B6F010

extern void _WriteMemory( int Address, int Value, int Bytes = 4 );
#define WriteMemory _WriteMemory