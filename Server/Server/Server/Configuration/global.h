#pragma once

typedef __int64 int64;

extern void _WriteMemory( int Address, int Value, int NumberOfBytes = 4 );
#define WriteMemory _WriteMemory



struct s_Packet
{
	int size;
	int opCode;

	int lParam;
	int wParam;
	int sParam;
	int eParam;
};