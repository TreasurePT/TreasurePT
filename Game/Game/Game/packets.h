#pragma once
class CPackets
{
public:
	void ReceivedPacket( int Packet );

private:
	enum CustomPacket
	{

	};

	enum Packet
	{
		Version = 0x4847008A,
	};
};

