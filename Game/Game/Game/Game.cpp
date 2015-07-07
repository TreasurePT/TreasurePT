#include "stdafx.h"
#include "assembly.h"

extern void __cdecl _SetTexts( );
extern int __cdecl _ReadConfiguration( );
extern int __cdecl _ShowVersion( HDC hDC );
extern void __cdecl _ReceivedPacket( s_Packet* Packet, LPARAM lParam );

class CGame
{
public: 
	std::shared_ptr<CAssembly> lpAsm = std::make_shared<CAssembly>( 0 );
	void WidescreenHook( );
	void PacketHook( );
	void UI_VersionHook( );
	void RemoveXTrap( );
};

void Main( )
{
	std::shared_ptr<CGame> lpGame = std::make_shared<CGame>( );
	EditData = VirtualAlloc( nullptr, 0x5000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
	_SetTexts( );

	lpGame->WidescreenHook( );
	lpGame->PacketHook( );
	lpGame->UI_VersionHook( );
	lpGame->RemoveXTrap( );
};

void CGame::WidescreenHook( )
{
	lpAsm->MakeBaseAddress( ( int )0x0044A080 );
	lpAsm->Jmp( ( int )&_ReadConfiguration );
};

void CGame::PacketHook( )
{
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
};

void CGame::UI_VersionHook( )
{
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