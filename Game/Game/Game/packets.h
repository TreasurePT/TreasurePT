#pragma once
class CPackets
{
public:
	void ReceivedPacket( s_Packet* Packet, LPARAM lParam );

private:
	enum CustomPacket
	{

	};

	enum Packet
	{
		AddExp = 0x48470031,
		Version = 0x4847008A,
	};
};