#pragma once

#define WIN32_LEAN_AND_MEAN
#include <SDKDDKVer.h>
#include <windows.h>
#include <strsafe.h>
#include <stdlib.h>
#include <memory>
#include <vector>


// Definições

#define PDATA 0x04B66010
#define IP "127.0.0.1"

#define LEVEL_CAP 100
#define LEVEL_MULTIPLIER 1.1f
#define LEVEL_EXP_BASE 100

extern const char* _Format( const char* String, ... );
#define Format _Format

extern void _WriteMemory( int Address, int Value, int Bytes = 4 );
#define WriteMemory _WriteMemory