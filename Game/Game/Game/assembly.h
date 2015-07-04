#pragma once

extern LPVOID PointerData, EditData;

#define EAX 1
#define ECX 2
#define EDX 3
#define EBX 4
#define ESP 5
#define EBP 6
#define ESI 7
#define EDI 8

class CAssembly
{
public:
	void MakeBaseAddress( int Address );
	void SetLastAddress( );
	void AtualizeAddress( void* Address, bool Last = false );
	void Push( int Var );
	void JmpPtr( int Address );
	void CallPtr( int Address );
	void Jmp( int Address );
	void Call( int Address );
	void Pop( int Var );
	void AddEsp( int Value );
	void Retn( int AddEsp = 0 );
	void Cmp( int Var, int Value );
	void Test( int Var1, int Var2 );
	void FillNops( int NumberOfNops, int Address = 0 );
	void PushPtrEsp( int Value );
	void LeaEax( int Value );
	CAssembly( ) { };
	CAssembly( int Address ) { MakeBaseAddress( Address ); };
protected:

private:
	int m_Address;
	int m_LastAddress;
	DWORD m_VP;
};