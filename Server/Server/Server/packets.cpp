#include "stdafx.h"
#include "Packets.h"
#include "file_manager.h"

CPackets::CPackets( )
{
	InitializeCriticalSection( &m_Send_Section );
}

void CPackets::SendPacket( char* Packet, int Player, bool IntegerOnly )
{
	EnterCriticalSection( &m_Send_Section );
	typedef void( __thiscall* t_SendPacket ) ( int, char*, int, int );
	t_SendPacket SendNumberPacket = ( t_SendPacket )0x00451E80;
	t_SendPacket SendStringPacket = ( t_SendPacket )0x00450DF0;

	if( IntegerOnly )
	{
		//SendNumberPacket( Player->GetSocket( ), Packet, *( int* )Packet, TRUE );
	}
	else
	{
		//SendStringPacket( Player->GetSocket( ), Packet, *( int* )Packet, TRUE );
	};
	LeaveCriticalSection( &m_Send_Section );
};

void CPackets::ReceivedPacket( s_Packet* Packet, int Player )
{
	switch( Packet->opCode )
	{
		case Packet::Connection:
			{

			}
			break;
	};

};

CPackets::~CPackets( )
{
	DeleteCriticalSection( &m_Send_Section );
}

void __cdecl _ReceivedPacket( s_Packet* Packet, int Player )
{
	std::shared_ptr<CPackets> lpPacket = std::make_shared<CPackets>( );
	lpPacket->ReceivedPacket( Packet, Player );
};