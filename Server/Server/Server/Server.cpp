#include "stdafx.h"
#include "file_manager.h"
#include "assembly.h"

extern void __cdecl _SetTexts( );
extern int __cdecl _CheckExpGained( int Exp, int Player );
extern void __cdecl _BuildItems( );
extern void __cdecl _ReceivedPacket( int Packet, int Player );
extern void __cdecl _SetLevels( );
extern int __cdecl _CheckLevelExp( int Level, __int64 Exp );
extern int __cdecl _GetLevelFromExp( __int64 Exp );
extern int __cdecl _CheckPlayerLevel( int Player );
extern void __cdecl _GetSoloExp( int MonsterInfo, int CharInfo, int Player );
extern int __cdecl _GetTotalExp( int Exp, int Level );

class CServer
{
public:
	std::shared_ptr<CAssembly> lpAsm = std::make_shared<CAssembly>( 0 );
	void PacketHook( );
	void CheckExpGainedHook( );
	void CheckLevelExpHook( );
	void GetLevelFromExpHook( );
	void CheckPlayerLevelHook( );
	void GetSoloExpHook( );
	void GetTotalExpHook( );
};

void Main( )
{
	std::shared_ptr<CServer> lpServer = std::make_shared<CServer>( );
	EditData = VirtualAlloc( nullptr, 0x5000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
	_SetTexts( );
	_BuildItems( );
	_SetLevels( );

	lpServer->PacketHook( );
	lpServer->CheckExpGainedHook( );
	lpServer->CheckLevelExpHook( );
	lpServer->GetLevelFromExpHook( );
	lpServer->CheckPlayerLevelHook( );
	lpServer->GetSoloExpHook( );
	lpServer->GetTotalExpHook( );
};

void CServer::PacketHook( )
{
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
};

void CServer::CheckExpGainedHook( )
{
	lpAsm->MakeBaseAddress( 0x00450099 );
	lpAsm->Push( EBP );
	lpAsm->PushPtrEsp( 0x14 );
	lpAsm->Call( ( int )&_CheckExpGained );
	lpAsm->AddEsp( 8 );
	lpAsm->Test( EAX, EAX );
	lpAsm->Jnz( 0x00450135 );
	lpAsm->FillNops( 112 );
};

void CServer::CheckLevelExpHook( )
{
	lpAsm->MakeBaseAddress( 0x004439E0 );
	lpAsm->Jmp( ( int )&_CheckLevelExp );
};

void CServer::GetLevelFromExpHook( )
{
	lpAsm->MakeBaseAddress( 0x00443A30 );
	lpAsm->Jmp( ( int )&_GetLevelFromExp );
};

void CServer::CheckPlayerLevelHook( )
{
	lpAsm->MakeBaseAddress( ( int )EditData );
	lpAsm->Push( EBX );
	lpAsm->Call( ( int )&_CheckPlayerLevel );
	lpAsm->Test( EAX, EAX );
	lpAsm->Je( 0x00571A43 );
	lpAsm->Jmp( 0x00571A04 );
	lpAsm->SetLastAddress( );
	lpAsm->MakeBaseAddress( ( int )0x005719FB );
	lpAsm->Jmp( ( int )EditData );
	lpAsm->FillNops( 4 );
	lpAsm->AtualizeAddress( &EditData, true );
};

void CServer::GetSoloExpHook( )
{
	lpAsm->MakeBaseAddress( 0x00560E2C );
	lpAsm->LeaEax( 0x20 );
	lpAsm->Push( EAX );
	lpAsm->Push( EDI );
	lpAsm->Push( EBX );
	lpAsm->Call( ( int )&_GetSoloExp );
	lpAsm->AddEsp( 12 );
	lpAsm->FillNops( 104 );
};

void CServer::GetTotalExpHook( )
{
	lpAsm->MakeBaseAddress( 0x0054FA40 );
	lpAsm->Jmp( ( int )&_GetTotalExp );
};