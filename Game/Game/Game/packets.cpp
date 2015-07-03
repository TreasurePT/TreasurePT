#include "stdafx.h"
#include "packets.h"

void CPackets::ReceivedPacket( int Packet, LPARAM lParam )
{
	switch( *( int* )( Packet + 4 ) )
	{

	};

};

void __cdecl _ReceivedPacket( int Packet, LPARAM lParam )
{
	std::shared_ptr<CPackets> lpPacket = std::make_shared<CPackets>( );
	lpPacket->ReceivedPacket( Packet, lParam );
};