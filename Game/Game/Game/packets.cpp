#include "stdafx.h"
#include "packets.h"
#include "level_manager.h"

void CPackets::ReceivedPacket( int Packet, LPARAM lParam )
{
	switch( *( int* )( Packet + 4 ) )
	{
		case CustomPacket::LoggedOn:
			{
				std::shared_ptr<CLevelManager> lpLevel = std::make_shared<CLevelManager>( );
				lpLevel->ReadLevels( *( int* )( Packet + 8 ),
									 *( float* )( Packet + 12 ),
									 *( int* )( Packet + 16 ) );
				lpLevel->WriteLevels( );
			}
			break;
		case Packet::AddPartyExp:
		case Packet::AddExp:
			{
				typedef DWORD( __cdecl* t_FindAutoPlayer ) ( DWORD );
				t_FindAutoPlayer FindAutoPlayer = ( t_FindAutoPlayer )0x0062D820;
				typedef DWORD( __cdecl* t_AddExp ) ( INT64 );
				t_AddExp AddExp = ( t_AddExp )0x00461D80;
				typedef void( __cdecl* t_AddChatMsg )( LPCSTR, INT );
				t_AddChatMsg AddChatMsg = ( t_AddChatMsg )0x0062DEB0;

				DWORD Char = FindAutoPlayer( *( DWORD* )( Packet + 24 ) );

				if( Char )
				{
					if( *( int* )( Packet + 24 ) - ( *( int* )( Packet + 8 ) & 0xFFFFFFFF ) != *( int* )( Packet + 20 ) )
					{
						*( int* )( Packet + 4 ) = NULL;
						return;
					};

					//TODO: CheckServerExp

					INT64 GainedExp = *( INT64 * )( Packet + 8 );
					DWORD LowBitExp = AddExp( GainedExp );

					*( DWORD* )( Char + 0x2B0 ) += LowBitExp;

					DWORD Monster_Code = *( DWORD* )( Char + 0x3A74 );

					std::string strExp( Format( "%d", LowBitExp ) );

					for( int i = strExp.size( ) - 3; i > 0; i -= 3 )
					{
						strExp.insert( strExp.begin( ) + i, ',' );
					}

					if( *( int* )( Packet + 4 ) == Packet::AddExp )
					{
						AddChatMsg( Format( "> Ganhou %s Exp.", strExp.c_str( ) ), 9 );
						//TODO: Quest Solo.
					}
					else
					{
						AddChatMsg( Format( "> Ganhou %s Exp em Grupo[ %d% / %d ].",
							strExp.c_str( ), *( int* )( Packet + 16 ) * 40 + 100, *( int* )( Packet + 16 ) ), 9 );
						//TODO: Quest Party.
					};

				};
				*( int* )( Packet + 4 ) = NULL;
			}
			break;
	};

};

void __cdecl _ReceivedPacket( int Packet, LPARAM lParam )
{
	std::shared_ptr<CPackets> lpPacket = std::make_shared<CPackets>( );
	lpPacket->ReceivedPacket( Packet, lParam );
};