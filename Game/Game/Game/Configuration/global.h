#pragma once

extern void _WriteMemory( int Address, int Value, int NumberOfBytes = 4 );
#define WriteMemory _WriteMemory

struct s_Packet
{
	SIZE_T Size;
	INT Opcode;
	LPARAM lParam;
	WPARAM wParam;
};