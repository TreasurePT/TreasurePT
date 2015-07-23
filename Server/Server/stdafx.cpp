#include "stdafx.h"

void _WriteMemory( int Address, int Value, int Bytes )
{
	DWORD VP = 0;
	VirtualProtect( ( LPVOID )Address, Bytes, PAGE_EXECUTE_READWRITE, &VP );
	switch( Bytes )
	{
		case 1:
			*( BYTE* )( Address ) = ( BYTE )Value;
			break;
		case 2:
			*( WORD* )( Address ) = ( WORD )Value;
			break;
		case 4:
			*( DWORD* )( Address ) = ( DWORD )Value;
			break;
	};
	VirtualProtect( ( LPVOID )Address, Bytes, VP, &VP );
};