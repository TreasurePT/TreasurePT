#pragma once

#define PDATA 0x04B66000
#define EDATA 0x04B67000
#define VDATA 0x04B6C000

extern void _WriteMemory( long Address, long Value, long NumberOfBytes = 4 );
#define WriteMemory _WriteMemory