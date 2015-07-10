#include "stdafx.h"
#include "Packets.h"
#include "file_manager.h"

CPackets::CPackets( )
{
	InitializeCriticalSection( &m_Send_Section );
}

void CPackets::ForceSend( char* Packet, int Player )
{
	EnterCriticalSection( &m_Send_Section );
	typedef void( __thiscall* t_SendPacket ) ( int, char*, int, int );
	t_SendPacket SendNumberPacket = ( t_SendPacket )0x00451E80;

	SendNumberPacket( Player, Packet, *( int* )Packet, TRUE );

	LeaveCriticalSection( &m_Send_Section );
};

void CPackets::SendPacket( char* Packet, int Player, bool IntegerOnly )
{
	EnterCriticalSection( &m_Send_Section );
	typedef void( __thiscall* t_SendPacket ) ( int, char*, int, int );
	t_SendPacket SendNumberPacket = ( t_SendPacket )0x00451E80;
	t_SendPacket SendStringPacket = ( t_SendPacket )0x00450DF0;

	if( IntegerOnly )
	{
		SendNumberPacket( *( int* )( Player + 0x06DFC ), Packet, *( int* )Packet, TRUE );
	}
	else
	{
		SendStringPacket( *( int* )( Player + 0x06DFC ), Packet, *( int* )Packet, TRUE );
	};
	LeaveCriticalSection( &m_Send_Section );
};

void CPackets::ReceivedPacket( int Packet, int Player )
{
	switch( *( int* )( Packet + 4 ) )
	{
		case Packet::Connection:
			{
				struct s_LoggedOn
				{
					int size;
					int opCode;

					int Level_Cap;
					float Level_Multiplier;
					int Level_Base_Exp;
				} Logged;
				Logged.size = sizeof( s_LoggedOn );
				Logged.opCode = 0x20150000;
				Logged.Level_Cap = LEVEL_CAP;
				Logged.Level_Multiplier = LEVEL_MULTIPLIER;
				Logged.Level_Base_Exp = LEVEL_BASE_EXP;

				SendPacket( ( char* )( &Logged ), Player, false );
			}
			break;
	};

};

CPackets::~CPackets( )
{
	DeleteCriticalSection( &m_Send_Section );
}

void __cdecl _ReceivedPacket( int Packet, int Player )
{
	std::shared_ptr<CPackets> lpPacket = std::make_shared<CPackets>( );
	lpPacket->ReceivedPacket( Packet, Player );
};