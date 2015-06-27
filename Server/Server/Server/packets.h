#pragma once
#include "player_info.h"

class CPackets
{
public:
	CPackets( );
	~CPackets( );
	int ReceivedPacket( int Packet, CPlayerInfo* Player );
	void SendPacket( void* Packet, CPlayerInfo* Player, bool IntegerOnly );
private:
	CRITICAL_SECTION m_Send_Section;
	char m_Buffer[ 256 ];

	enum CustomPacket
	{

	};

	enum Packet
	{
		Connection = 0x48470085,
	};
};