#pragma once
#include "stdafx.h"

class CPlayerInfo
{
public:
	//Construtor com o endereço do player.
	CPlayerInfo( int Address ) { m_Address = Address; };
	void SetAddress( int Address ) { m_Address = Address; };

	//Retorna o nível de privilégio do jogador.
	int GetPrivilege( ) { return *( int* )( m_Address + 0x6E1C ); };
	void SetPrivilege( int Privilege ) { *( int* )( m_Address + 0x6E1C ) = Privilege; };

	//Retorna o nível do jogador;
	int GetLevel( ) { return *( int* )( m_Address + 0xC8 ); };
	void SetLevel( int Level ) { *( int* )( m_Address + 0xC8 ) = Level; };


	//Soquete alocado.
	int GetSocket( ) { return *( int* )( m_Address + 0x06DFC ); };

	//Possibilita o operador =.
	operator int( ) const { return m_Address; };
	//Possibilita o operador +.
	int operator+( int x ) { return m_Address; };
private:
	int m_Address;
};