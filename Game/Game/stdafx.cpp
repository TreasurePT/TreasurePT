#include "stdafx.h"

const char* _Format( const char* String, ... )
{
	static char Buffer[ 512 ] = { 0 };
	va_list Args = { 0 };
	va_start( Args, String );
	StringCbVPrintfA( Buffer, 512, String, Args );
	return Buffer;
};

void _WriteMemory( int Address, int Value, int Bytes )
{
	DWORD VP = 0;
	VirtualProtect( ( LPVOID )( Address ), Bytes, PAGE_EXECUTE_READWRITE, &VP );
	switch( Bytes )
	{
		case 1:
			*( char* )( Address ) = ( char )Value;
			break;
		case 2:
			*( short* )( Address ) = ( short )Value;
			break;
		case 4:
			*( int* )( Address ) = Value;
			break;
	};
	VirtualProtect( ( LPVOID )( Address ), Bytes, VP, &VP );
};