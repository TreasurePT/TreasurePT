#include "stdafx.h"
#include "Packets.h"
#include "file_manager.h"

CPackets::CPackets( )
{
	InitializeCriticalSection( &m_Send_Section );
}

void CPackets::SendPacket( void* Packet, CPlayerInfo* Player, bool IntegerOnly )
{
	EnterCriticalSection( &m_Send_Section );
	typedef void( __thiscall* t_SendPacket ) ( int, void *, int, int );
	t_SendPacket SendNumberPacket = ( t_SendPacket )0x00451E80;
	t_SendPacket SendStringPacket = ( t_SendPacket )0x00450DF0;

	if( IntegerOnly )
	{
		SendNumberPacket( Player->GetSocket( ), Packet, *( int* )Packet, TRUE );
	}
	else
	{
		SendStringPacket( Player->GetSocket( ), Packet, *( int* )Packet, TRUE );
	};
	LeaveCriticalSection( &m_Send_Section );
};

int CPackets::ReceivedPacket( int Packet, CPlayerInfo* Player )
{
	Player->SetAddress( ( int )Player );

	switch( *( int* )( Packet + 4 ) )
	{
		case Packet::Connection:
			{

			}
			break;
	};

	return Packet;
};

CPackets::~CPackets( )
{
	DeleteCriticalSection( &m_Send_Section );
}
