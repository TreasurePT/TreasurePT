#include "stdafx.h"
#include "packets.h"

Packets::Packets( )
{
	InitializeCriticalSection( &Section );
}

void Packets::SendInt( char* Packet, int Player )
{
	EnterCriticalSection( &Section );
	Size = *( int* )( Packet );
	Socket = *( int* )( Player + 0x6DFC );
	SendNumberPacket( Socket, Packet, Size, TRUE );
	LeaveCriticalSection( &Section );
};

void Packets::SendString( char* Packet, int Player )
{
	EnterCriticalSection( &Section );
	Size = *( int* )( Packet );
	Socket = *( int* )( Player + 0x6DFC );
	SendStringPacket( Socket, Packet, Size, TRUE );
	LeaveCriticalSection( &Section );
};

Packets::~Packets( )
{
	DeleteCriticalSection( &Section );
}
