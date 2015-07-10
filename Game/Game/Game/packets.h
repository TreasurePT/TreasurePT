#pragma once
class CPackets
{
public:
	void ReceivedPacket( int Packet, LPARAM lParam );

private:
	enum CustomPacket
	{
		LoggedOn = 0x20150000,
	};

	enum Packet
	{
		AddPartyExp = 0x48470029,
		AddExp = 0x48470031,
		Version = 0x4847008A,
	};
};