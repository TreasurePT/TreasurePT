#pragma once

extern void _WriteMemory( long Address, long Value, long NumberOfBytes = 4 );
#define WriteMemory _WriteMemory