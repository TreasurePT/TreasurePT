#include "stdafx.h"
#include "assembly.h"
#include "sql_api.h"
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>

extern void __cdecl _SetTexts( );
extern int __cdecl _CheckExpGained( int Exp, int Player );
extern void __cdecl _BuildItems( );
extern void __cdecl _ReceivedPacket( int Packet, int Player );
extern void __cdecl _SetLevels( );
extern int __cdecl _CheckLevelExp( int Level, __int64 Exp );
extern int __cdecl _GetLevelFromExp( __int64 Exp );
extern int __cdecl _CheckPlayerLevel( int Player );
extern void __cdecl _GetSoloExp( int MonsterInfo, int CharInfo );
extern int __cdecl _GetTotalExp( int Exp, int Level );
extern void __cdecl _GetPartyExp( int MonsterInfo, int PartyInfo );
extern void __cdecl _Field( );

class CServer : public CSQLApi
{
public:
	std::shared_ptr<CAssembly> lpAsm = std::make_shared<CAssembly>( 0 );
	void ConnectToSql( );
	void PacketHook( );
	void CheckExpGainedHook( );
	void CheckLevelExpHook( );
	void GetLevelFromExpHook( );
	void CheckPlayerLevelHook( );
	void GetSoloExpHook( );
	void GetTotalExpHook( );
	void GetPartyExpHook( );
	void FieldHook( );
};

void Main( )
{
	std::shared_ptr<CServer> lpServer = std::make_shared<CServer>( );
	EditData = VirtualAlloc( nullptr, 0x5000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
	_SetTexts( );
	_BuildItems( );
	_SetLevels( );

	lpServer->ConnectToSql( );
	lpServer->PacketHook( );
	lpServer->CheckExpGainedHook( );
	lpServer->CheckLevelExpHook( );
	lpServer->GetLevelFromExpHook( );
	lpServer->CheckPlayerLevelHook( );
	lpServer->GetSoloExpHook( );
	lpServer->GetTotalExpHook( );
	lpServer->GetPartyExpHook( );
	lpServer->FieldHook( );
};

void CServer::ConnectToSql( )
{
	const char* SQLString = "DRIVER={SQL Server};SERVER=TPT\\SQLExpress;UID=sa;PWD=123456;";
	SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &s_Env );
	SQLSetEnvAttr( s_Env, SQL_ATTR_ODBC_VERSION, ( SQLPOINTER )SQL_OV_ODBC3, 0 );
	SQLAllocHandle( SQL_HANDLE_DBC, s_Env, &s_Conn );
	SQLDriverConnectA( s_Conn, NULL, ( SQLCHAR* )( SQLString ),
					   SQL_NTS, NULL, NULL, NULL, SQL_DRIVER_NOPROMPT );
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
	lpAsm->AddEsp( 4 );
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
	lpAsm->Push( EDI );
	lpAsm->Push( EBX );
	lpAsm->Call( ( int )&_GetSoloExp );
	lpAsm->AddEsp( 8 );
	lpAsm->FillNops( 109 );
};

void CServer::GetTotalExpHook( )
{
	lpAsm->MakeBaseAddress( 0x0054FA40 );
	lpAsm->Jmp( ( int )&_GetTotalExp );
};

void CServer::GetPartyExpHook( )
{
	lpAsm->MakeBaseAddress( 0x00575020 );
	lpAsm->Push( ECX );
	lpAsm->PushPtrEsp( 0x4 );
	lpAsm->Call( ( int )&_GetPartyExp );
	lpAsm->AddEsp( 8 );
	lpAsm->Retn( 8 );
};

void CServer::FieldHook( )
{
	lpAsm->MakeBaseAddress( 0x00430430 );
	lpAsm->Jmp( ( int )&_Field );
};