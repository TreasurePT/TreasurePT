#include "stdafx.h"
#include "main.h"

extern void __cdecl Game_Settings( );

//Função principal.
void Game( )
{
	*( DWORD* )( PDATA + 0 ) = ( DWORD )&Game_Settings;
};