#include "stdafx.h"
#include "packets.h"

void CPackets::ReceivedPacket( s_Packet* Packet, LPARAM lParam )
{
	switch( Packet->Opcode )
	{

	};

};

void __cdecl _ReceivedPacket( s_Packet* Packet, LPARAM lParam )
{
	std::shared_ptr<CPackets> lpPacket = std::make_shared<CPackets>( );
	lpPacket->ReceivedPacket( Packet, lParam );
};