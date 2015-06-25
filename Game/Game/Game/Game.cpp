#include "stdafx.h"

extern void __cdecl _SetTexts( );
extern int __cdecl _ReadConfiguration( );

class CGame
{
public:

	void RemoveXTrap( );
	void Main( );
};

void Main( )
{
	std::shared_ptr<CGame> lpGame = std::make_shared<CGame>( );
	return lpGame->Main( );
};

void _CreateItems( );

void CGame::Main( )
{
	_SetTexts( );
	RemoveXTrap( );

	_CreateItems( );

	*( long* )( PDATA + 0 ) = ( long )( &_ReadConfiguration );
};


void CGame::RemoveXTrap( )
{
	WriteMemory( 0x0078FA40, 0xC3, 1 );
	WriteMemory( 0x0078F5A0, 0xC3, 1 );
	WriteMemory( 0x0078F558, 0xC3, 1 );
	WriteMemory( 0x0078F530, 0xC3, 1 );
};


void _CreateItems( )
{
	FILE* lpFile = nullptr;
	fopen_s( &lpFile, "Items.txt", "a" );
	char newcode[ 6 ] = { 0 };
	char newcode2[ 6 ] = { 0 };
	for( int i = 0x00840E00; i < 0x00840E00 + 5000 * 0x314; i += 0x314 )
	{
		for( int c = 0; c < 5; c++ )
		{
			newcode[ c ] = *( BYTE* )( i + 0x24 + c);
			newcode2[ c ] = (char)std::tolower( newcode[ c ] );
			newcode[ c ] = (char)std::toupper( newcode2[ c ] );
		};
		fprintf( lpFile, "CreateItem( 0x%08X, \"%s\", \"%s\", 0x%02X, 0x%02X, \"%s\", 0x%X, 0x%X, 0x%X, 0x%X, %d );\n",
				 *( DWORD* )( i ), newcode, newcode2,
				 *( DWORD* )( i + 0x34 ), *( DWORD* )( i + 0x38 ), ( char* )( i + 0x3C ),
				 *( DWORD* )( i + 0x7C ), *( DWORD* )( i + 0xC0 ), *( DWORD* )( i + 0xC4 ),
				 *( DWORD* )( i + 0xC8 ), *( BYTE* )( i + 0x7D ) );
	};
};