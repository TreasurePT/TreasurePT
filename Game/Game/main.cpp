#include "stdafx.h"
#include "main.h"

extern void __cdecl Game_Settings( );
extern void __cdecl Initialize_New_Armors( );

//Função principal.
void Game( )
{
	*( DWORD* )( PDATA + 0 ) = ( DWORD )&Game_Settings;

	Initialize_New_Armors( );
};