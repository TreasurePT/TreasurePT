#pragma once

extern void _WriteMemory( int Address, int Value, int NumberOfBytes = 4 );
#define WriteMemory _WriteMemory