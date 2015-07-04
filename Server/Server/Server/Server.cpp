#include "stdafx.h"
#include "file_manager.h"
#include "assembly.h"

extern void __cdecl _SetTexts( );
extern int __cdecl _CheckExpGained( int Exp, int Player );
extern void __cdecl _BuildItems( );
extern void __cdecl _ReceivedPacket( s_Packet* Packet, int Player );

class CServer
{
public:
	void Main( );
private:
	char m_Buffer[ 256 ];
};

void CServer::Main( )
{
	std::shared_ptr<CAssembly> lpAsm = std::make_shared<CAssembly>( 0 );
	_SetTexts( );
	_BuildItems( );

	// Chamada dos Pacotes
	lpAsm->MakeBaseAddress( ( int )EditData );
	lpAsm->Push( EAX );
	lpAsm->Push( EBP );
	lpAsm->Push( EDI );
	lpAsm->Call( ( int )&_ReceivedPacket );
	lpAsm->AddEsp( 8 );
	lpAsm->Pop( EAX );
	lpAsm->Cmp( ESI, 0x48478400 );
	lpAsm->Jmp( 0x0056F527 );
	lpAsm->SetLastAddress( );
	lpAsm->MakeBaseAddress( ( int )0x0056F521 );
	lpAsm->Jmp( ( int )EditData );
	lpAsm->FillNops( 1 );
	lpAsm->AtualizeAddress( &EditData, true );

	// Chamada da Checagem de ExperiÍncia Ganha
	lpAsm->MakeBaseAddress( 0x00450099 );
	lpAsm->Push( EBP );
	lpAsm->PushPtrEsp( 0x14 );
	lpAsm->Call( ( int )&_CheckExpGained );
	lpAsm->AddEsp( 8 );
	lpAsm->Test( EAX, EAX );
	lpAsm->Jnz( 0x00450135 );
	lpAsm->FillNops( 112 );

		//*( int* )( PDATA + 0 ) = ( int )( &_CheckExpGained );
};












void Main( )
{
	EditData = VirtualAlloc( nullptr, 0x5000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
	std::shared_ptr<CServer> lpServer = std::make_shared<CServer>( );
	return lpServer->Main( );
};