#pragma once

class CPackets
{
public:
	CPackets( );
	~CPackets( );
	void ReceivedPacket( s_Packet* Packet, int Player );
	void SendPacket( void* Packet, int Player, bool IntegerOnly );
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