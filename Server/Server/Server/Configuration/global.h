#pragma once

typedef __int64 int64;

extern void _WriteMemory( int Address, int Value, int NumberOfBytes = 4 );
#define WriteMemory _WriteMemory

extern const char* _Format( const char* String, ... );
#define Format _Format

extern void _Clear( char* String, size_t Size );
#define Clear _Clear