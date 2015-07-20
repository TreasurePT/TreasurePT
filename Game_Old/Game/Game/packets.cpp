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
				std::shared_ptr<CLevelManager> lpLevel = std::make_shared<CLevelManager>( );
				lpLevel->AddExpSystem( Packet );
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