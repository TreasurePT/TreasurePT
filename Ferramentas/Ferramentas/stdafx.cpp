#include "stdafx.h"

const char* _Format( const char* String, ... )
{
	static char Buffer[ 1024 ] = { 0 };
	SecureZeroMemory( Buffer, 1024 );
	va_list Args = { 0 };
	va_start( Args, String );
	StringCbVPrintfA( Buffer, 1024, String, Args );
	va_end( Args );
	return Buffer;
};