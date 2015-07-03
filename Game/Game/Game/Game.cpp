#include "stdafx.h"
#include "assembly.h"

extern void __cdecl _SetTexts( );
extern int __cdecl _ReadConfiguration( );
extern int __cdecl _ShowVersion( HDC hDC );
extern void __cdecl _ReceivedPacket( int Packet, LPARAM lParam );

class CGame
{
public:

	void RemoveXTrap( );
	void Main( );
};

void Main( )
{
	EditData = VirtualAlloc( nullptr, 0x5000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
	std::shared_ptr<CGame> lpGame = std::make_shared<CGame>( );
	return lpGame->Main( );
};

void CGame::Main( )
{
	std::shared_ptr<CAssembly> lpAsm = std::make_shared<CAssembly>( );
	_SetTexts( );
	RemoveXTrap( );

	// Chamada da Widescreen
	lpAsm->MakeBaseAddress( ( int )0x0044A080 );
	lpAsm->Jmp( ( int )&_ReadConfiguration );

	// Chamada dos Pacotes
	lpAsm->MakeBaseAddress( ( int )EditData );
	lpAsm->Push( EAX );
	lpAsm->Push( EBX );
	lpAsm->Push( EDI );
	lpAsm->Call( ( int )&_ReceivedPacket );
	lpAsm->AddEsp( 8 );
	lpAsm->Pop( EAX );
	lpAsm->Cmp( EAX, 0x48478300 );
	lpAsm->Jmp( 0x0063BB04 );
	lpAsm->SetLastAddress( );
	lpAsm->MakeBaseAddress( ( int )0x0063BAFF );
	lpAsm->Jmp( ( int )EditData );
	lpAsm->AtualizeAddress( &EditData, true );

	// Chamada da UI ( Versão )
	lpAsm->MakeBaseAddress( ( int )0x005A94D6 );
	lpAsm->PushPtrEsp( 0x20 );
	lpAsm->Call( ( int )&_ShowVersion );
	lpAsm->AddEsp( 4 );
	lpAsm->FillNops( 113 );
	lpAsm->Test( EAX, EAX );
};

void CGame::RemoveXTrap( )
{
	WriteMemory( 0x0078FA40, 0xC3, 1 );
	WriteMemory( 0x0078F5A0, 0xC3, 1 );
	WriteMemory( 0x0078F558, 0xC3, 1 );
	WriteMemory( 0x0078F530, 0xC3, 1 );
};