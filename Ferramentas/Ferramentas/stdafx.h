#pragma once

#define WIN32_LEAN_AND_MEAN
#include <SDKDDKVer.h>
#include <windows.h>
#include <strsafe.h>
#include <stdlib.h>
#include <memory>


// Defini��es

extern const char* _Format( const char* String, ... );
#define Format _Format