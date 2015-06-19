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
/*
void BUG( )
{
	FILE* lpFile = nullptr;
	fopen_s( &lpFile, "Sou_Legal.txt", "a" );
	int inicio_dos_nomes = 0x006808A0;
	int inicio_das_desc = 0x006808E0;

	while(true)
	{
		fprintf( lpFile, "lpSkillTranslate->Name( \"%s\" );\n", (char*)inicio_dos_nomes );
		fprintf( lpFile, "lpSkillTranslate->Description( \"%s\" );\n", ( char* )inicio_das_desc );
		inicio_dos_nomes += 0x12C;
		inicio_das_desc += 0x12C;
		if( *(BYTE*)inicio_dos_nomes == 0)
			break;
	};
};
*/
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