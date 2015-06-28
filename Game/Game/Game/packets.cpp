#include "stdafx.h"
#include "packets.h"

void CPackets::ReceivedPacket( int Packet )
{
	LPARAM lParam = *( LPARAM* )( 0x04B67056 );
	switch( *( int* )( Packet + 4 ) )
	{
		case Packet::Version:
			{
				typedef void( __cdecl* t_SetGameError )( int Error );
				t_SetGameError SetGameError = ( t_SetGameError )0x005891D0;
				if( *( int* )( 0x03AD1F8C ) == *( int* )( lParam ) )
				{
					memcpy_s( ( void* )0x03A80F30, sizeof( int ) * 6, ( void* )( lParam + 0x2C ), sizeof( int ) * 6 );
				};
				if( *( int* )( 0x03AD1F88 ) == *( int* )( lParam ) || *( int* )( 0x03AD1F8C ) == *( int* )( lParam ) )
				{
					if( VERSION != *( int* )( Packet + 12 ) )
					{
						if( *( int* )( 0x03AD1F88 ) == 0 || *( int* )( 0x03AD1F8C ) == 0 )
						{
							SetGameError( 1 );
							break;
						};
					};
				};
				SetGameError( 0 );
			}
			break;
	};
};

void __cdecl _ReceivedPacket( int Packet )
{
	std::shared_ptr<CPackets> lpPacket = std::make_shared<CPackets>( );
	lpPacket->ReceivedPacket( Packet );
};