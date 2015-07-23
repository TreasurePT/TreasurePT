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

extern const char* _Format( const char* String, ... );
#define Format _Format