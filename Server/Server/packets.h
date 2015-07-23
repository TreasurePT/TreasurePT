#pragma once

class Packets
{
private:
	typedef void( __thiscall* t_SendPacket ) ( int, char*, int, int );
public:
	Packets( );
	~Packets( );
	t_SendPacket SendNumberPacket = ( t_SendPacket )0x00451E80;
	t_SendPacket SendStringPacket = ( t_SendPacket )0x00450DF0;
	void SendInt( char* Packet, int Player );
	void SendString( char* Packet, int Player );
private:
	CRITICAL_SECTION Section;
	int Size, Socket;
};

