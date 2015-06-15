#include "stdafx.h"

extern void __cdecl _SetTexts( );

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

void CGame::Main( )
{
	_SetTexts( );
	RemoveXTrap( );
};

void CGame::RemoveXTrap( )
{
	WriteMemory( 0x0078FA40, 0xC3, 1 );
	WriteMemory( 0x0078F5A0, 0xC3, 1 );
	WriteMemory( 0x0078F558, 0xC3, 1 );
	WriteMemory( 0x0078F530, 0xC3, 1 );
};