#include "stdafx.h"
#include "global.h"

void _WriteMemory( int Address, int Value, int NumberOfBytes )
{
	DWORD VP = 0;
	VirtualProtect( ( void* )( Address ), 4, PAGE_EXECUTE_READWRITE, &VP );
	switch( NumberOfBytes )
	{
		case 1:
			*( char* )( Address ) = ( char )( Value );
			break;
		case 2:
			*( short* )( Address ) = ( short )( Value );
			break;
		case 4:
			*( int* )( Address ) = ( int )( Value );
			break;
	}
	VirtualProtect( ( void* )( Address ), 4, VP, &VP );
};