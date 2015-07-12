#include "stdafx.h"
#include "Assembly.h"

LPVOID EditData = nullptr;

void CAssembly::SetLastAddress( )
{
	m_LastAddress = m_Address;
};

void CAssembly::AtualizeAddress( void* Address, bool Last )
{
	if( Last )
	{
		FillNops( 4, m_LastAddress );
		m_LastAddress += 4;
		*( int* )Address = ( int )m_LastAddress;
	}
	else
	{
		FillNops( 4 );
		*( int* )Address = m_Address;
	};
};

void CAssembly::MakeBaseAddress( int Address )
{
	m_Address = ( int )Address;
};

void CAssembly::Push( int Var )
{
	if( Var <= EDI && Var >= 1 )
	{
		VirtualProtect( ( void* )( m_Address ), 1, PAGE_EXECUTE_READWRITE, &m_VP );
		*( BYTE* )( m_Address ) = 0x4F + Var;
		m_VP = m_VP;
		VirtualProtect( ( void* )( m_Address ), 1, m_VP, &m_VP );
		m_Address += 1;
	}
	else if( Var <= 127 && Var >= -128 )
	{
		VirtualProtect( ( void* )( m_Address ), 2, PAGE_EXECUTE_READWRITE, &m_VP );
		*( BYTE* )( m_Address ) = 0x6A;
		*( BYTE* )( m_Address + 1 ) = Var;
		m_VP = m_VP;
		VirtualProtect( ( void* )( m_Address ), 2, m_VP, &m_VP );
		m_Address += 2;
	}
	else if( Var > 127 || Var < -128 )
	{
		VirtualProtect( ( void* )( m_Address ), 5, PAGE_EXECUTE_READWRITE, &m_VP );
		*( BYTE* )( m_Address ) = 0x68;
		*( int* )( m_Address + 1 ) = Var;
		m_VP = m_VP;
		VirtualProtect( ( void* )( m_Address ), 5, m_VP, &m_VP );
		m_Address += 5;
	};
};

void CAssembly::JmpPtr( int Address )
{
	VirtualProtect( ( void* )( m_Address ), 6, PAGE_EXECUTE_READWRITE, &m_VP );
	*( WORD* )( m_Address ) = 0x25FF;
	m_VP = m_VP;
	*( int* )( m_Address + 2 ) = Address;
	VirtualProtect( ( void* )( m_Address ), 6, m_VP, &m_VP );
	m_Address += 6;
};

void CAssembly::CallPtr( int Address )
{
	VirtualProtect( ( void* )( m_Address ), 6, PAGE_EXECUTE_READWRITE, &m_VP );
	*( WORD* )( m_Address ) = 0x15FF;
	m_VP = m_VP;
	*( int* )( m_Address + 2 ) = Address;
	VirtualProtect( ( void* )( m_Address ), 6, m_VP, &m_VP );
	m_Address += 6;
};

void CAssembly::Jmp( int Address )
{
	if( Address - m_Address <= 127 && Address - m_Address >= -128 )
	{
		VirtualProtect( ( void* )( m_Address ), 2, PAGE_EXECUTE_READWRITE, &m_VP );
		*( BYTE* )( m_Address ) = 0xEB;
		m_VP = m_VP;
		*( int* )( m_Address + 1 ) = ( Address - m_Address ) - 2;
		VirtualProtect( ( void* )( m_Address ), 2, m_VP, &m_VP );
		m_Address += 2;
	}
	else if( Address - m_Address > 127 || Address - m_Address < -128 )
	{
		VirtualProtect( ( void* )( m_Address ), 5, PAGE_EXECUTE_READWRITE, &m_VP );
		*( BYTE* )( m_Address ) = 0xE9;
		m_VP = m_VP;
		*( int* )( m_Address + 1 ) = ( Address - m_Address ) - 5;
		VirtualProtect( ( void* )( m_Address ), 5, m_VP, &m_VP );
		m_Address += 5;
	};
};

void CAssembly::Call( int Address )
{
	VirtualProtect( ( void* )( m_Address ), 5, PAGE_EXECUTE_READWRITE, &m_VP );
	*( BYTE* )( m_Address ) = 0xE8;
	m_VP = m_VP;
	*( int* )( m_Address + 1 ) = ( Address - m_Address ) - 5;
	VirtualProtect( ( void* )( m_Address ), 5, m_VP, &m_VP );
	m_Address += 5;
};

void CAssembly::Pop( int Var )
{
	if( Var <= EDI && Var >= 1 )
	{
		VirtualProtect( ( void* )( m_Address ), 1, PAGE_EXECUTE_READWRITE, &m_VP );
		*( BYTE* )( m_Address ) = 0x57 + Var;
		m_VP = m_VP;
		VirtualProtect( ( void* )( m_Address ), 1, m_VP, &m_VP );
		m_Address += 1;
	}
};

void CAssembly::AddEsp( int Value )
{
	if( Value != 0 && Value <= 127 && Value >= -128 )
	{
		VirtualProtect( ( void* )( m_Address ), 3, PAGE_EXECUTE_READWRITE, &m_VP );
		*( WORD* )( m_Address ) = 0xC483;
		m_VP = m_VP;
		*( BYTE* )( m_Address + 2 ) = Value;
		VirtualProtect( ( void* )( m_Address ), 3, m_VP, &m_VP );
		m_Address += 3;
	}
	else if( Value != 0 && Value > 127 || Value < -128 )
	{
		VirtualProtect( ( void* )( m_Address ), 6, PAGE_EXECUTE_READWRITE, &m_VP );
		*( WORD* )( m_Address ) = 0xC481;
		m_VP = m_VP;
		*( int* )( m_Address + 2 ) = Value;
		VirtualProtect( ( void* )( m_Address ), 6, m_VP, &m_VP );
		m_Address += 6;
	};
};

void CAssembly::Retn( int AddEsp )
{
	if( AddEsp == 0 )
	{
		VirtualProtect( ( void* )( m_Address ), 1, PAGE_EXECUTE_READWRITE, &m_VP );
		*( BYTE* )( m_Address ) = 0xC3;
		m_VP = m_VP;
		VirtualProtect( ( void* )( m_Address ), 1, m_VP, &m_VP );
		m_Address += 1;
	}
	else if( AddEsp > 0 )
	{
		VirtualProtect( ( void* )( m_Address ), 3, PAGE_EXECUTE_READWRITE, &m_VP );
		*( BYTE* )( m_Address ) = 0xC2;
		m_VP = m_VP;
		*( WORD* )( m_Address + 1 ) = AddEsp;
		VirtualProtect( ( void* )( m_Address ), 3, m_VP, &m_VP );
		m_Address += 3;
	};
};

void CAssembly::Cmp( int Var, int Value )
{
	if( Var <= EDI && Var >= 1 )
	{
		if( Var == EAX )
		{
			if( Value <= 127 && Value >= -128 )
			{
				VirtualProtect( ( void* )( m_Address ), 3, PAGE_EXECUTE_READWRITE, &m_VP );
				*( WORD* )( m_Address ) = 0xF883;
				m_VP = m_VP;
				*( BYTE* )( m_Address + 2 ) = ( BYTE )Value;
				VirtualProtect( ( void* )( m_Address ), 3, m_VP, &m_VP );
				m_Address += 3;
			}
			else if( Value > 127 || Value < -128 )
			{
				VirtualProtect( ( void* )( m_Address ), 5, PAGE_EXECUTE_READWRITE, &m_VP );
				*( BYTE* )( m_Address ) = 0x3D;
				m_VP = m_VP;
				*( int* )( m_Address + 1 ) = ( int )Value;
				VirtualProtect( ( void* )( m_Address ), 5, m_VP, &m_VP );
				m_Address += 5;
			};
		}
		else
		{
			if( Value <= 127 && Value >= -128 )
			{
				VirtualProtect( ( void* )( m_Address ), 3, PAGE_EXECUTE_READWRITE, &m_VP );
				*( WORD* )( m_Address ) = 0xF783 + ( Var * 0x100 );
				m_VP = m_VP;
				*( BYTE* )( m_Address + 2 ) = ( BYTE )Value;
				VirtualProtect( ( void* )( m_Address ), 3, m_VP, &m_VP );
				m_Address += 3;
			}
			else if( Value > 127 || Value < -128 )
			{
				VirtualProtect( ( void* )( m_Address ), 6, PAGE_EXECUTE_READWRITE, &m_VP );
				*( WORD* )( m_Address ) = 0xF781 + ( Var * 0x100 );
				m_VP = m_VP;
				*( int* )( m_Address + 2 ) = ( int )Value;
				VirtualProtect( ( void* )( m_Address ), 6, m_VP, &m_VP );
				m_Address += 6;
			};
		};
	};
};

void CAssembly::Test( int Var1, int Var2 )
{
	if( Var1 != Var2 )
		return;
	VirtualProtect( ( void* )( m_Address ), 2, PAGE_EXECUTE_READWRITE, &m_VP );
	switch( Var1 )
	{
		case EAX:*( WORD* )( m_Address ) = 0xC085; break;
		case ECX:*( WORD* )( m_Address ) = 0xC985; break;
		case EDX:*( WORD* )( m_Address ) = 0xD285; break;
		case EBX:*( WORD* )( m_Address ) = 0xDB85; break;
		case ESP:*( WORD* )( m_Address ) = 0xE585; break;
		case EBP:*( WORD* )( m_Address ) = 0xED85; break;
		case ESI:*( WORD* )( m_Address ) = 0xF685; break;
		case EDI:*( WORD* )( m_Address ) = 0xFF85; break;
		default: m_Address += 2; break;
	};
	VirtualProtect( ( void* )( m_Address ), 2, m_VP, &m_VP );
};

void CAssembly::FillNops( int NumberOfNops, int Address )
{
	if( Address == 0 )
	{
		if( NumberOfNops != 0 )
		{
			for( int i = 0; i < NumberOfNops; i++ )
			{
				VirtualProtect( ( void* )( m_Address ), 1, PAGE_EXECUTE_READWRITE, &m_VP );
				*( BYTE* )( m_Address ) = 0x90;
				m_VP = m_VP;
				VirtualProtect( ( void* )( m_Address ), 1, m_VP, &m_VP );
				m_Address += 1;
			};
		};
	}
	else
	{
		if( NumberOfNops != 0 )
		{
			for( int i = 0; i < NumberOfNops; i++ )
			{
				VirtualProtect( ( void* )( Address ), 1, PAGE_EXECUTE_READWRITE, &m_VP );
				*( BYTE* )( Address ) = 0x90;
				m_VP = m_VP;
				VirtualProtect( ( void* )( Address ), 1, m_VP, &m_VP );
				Address += 1;
			};
		};
	};
};

void CAssembly::PushPtrEsp( int Value )
{
	if( Value == 0 )
	{
		VirtualProtect( ( void* )( m_Address ), 3, PAGE_EXECUTE_READWRITE, &m_VP );
		*( BYTE* )( m_Address ) = 0xFF;
		*( WORD* )( m_Address + 1 ) = 0x2434;
		m_VP = m_VP;
		VirtualProtect( ( void* )( m_Address ), 3, m_VP, &m_VP );
		m_Address += 3;
	}
	else if( Value <= 127 && Value >= -128 )
	{
		VirtualProtect( ( void* )( m_Address ), 4, PAGE_EXECUTE_READWRITE, &m_VP );
		*( BYTE* )( m_Address ) = 0xFF;
		*( WORD* )( m_Address + 1 ) = 0x2474;
		*( BYTE* )( m_Address + 3 ) = Value;
		m_VP = m_VP;
		VirtualProtect( ( void* )( m_Address ), 4, m_VP, &m_VP );
		m_Address += 4;
	}
	else if( Value > 127 || Value < -128 )
	{
		VirtualProtect( ( void* )( m_Address ), 7, PAGE_EXECUTE_READWRITE, &m_VP );
		*( BYTE* )( m_Address ) = 0xFF;
		*( WORD* )( m_Address + 1 ) = 0x24B4;
		*( int* )( m_Address + 3 ) = Value;
		m_VP = m_VP;
		VirtualProtect( ( void* )( m_Address ), 7, m_VP, &m_VP );
		m_Address += 7;
	};
};

void CAssembly::LeaEax( int Value )
{
	if( Value == 0 )
	{
		VirtualProtect( ( void* )( m_Address ), 3, PAGE_EXECUTE_READWRITE, &m_VP );
		*( BYTE* )( m_Address ) = 0x8D;
		*( WORD* )( m_Address + 1 ) = 0x2400;
		m_VP = m_VP;
		VirtualProtect( ( void* )( m_Address ), 3, m_VP, &m_VP );
		m_Address += 3;
	}
	else if( Value <= 127 && Value >= -128 )
	{
		VirtualProtect( ( void* )( m_Address ), 4, PAGE_EXECUTE_READWRITE, &m_VP );
		*( BYTE* )( m_Address ) = 0x8D;
		*( WORD* )( m_Address + 1 ) = 0x2444;
		*( BYTE* )( m_Address + 3 ) = Value;
		m_VP = m_VP;
		VirtualProtect( ( void* )( m_Address ), 4, m_VP, &m_VP );
		m_Address += 4;
	}
	else if( Value > 127 || Value < -128 )
	{
		VirtualProtect( ( void* )( m_Address ), 7, PAGE_EXECUTE_READWRITE, &m_VP );
		*( BYTE* )( m_Address ) = 0x8D;
		*( WORD* )( m_Address + 1 ) = 0x2484;
		*( int* )( m_Address + 3 ) = Value;
		m_VP = m_VP;
		VirtualProtect( ( void* )( m_Address ), 7, m_VP, &m_VP );
		m_Address += 7;
	};
};

void CAssembly::ImulEaxEax( int Value )
{
	if( Value > 127 || Value < -128 )
	{
		VirtualProtect( ( void* )( m_Address ), 6, PAGE_EXECUTE_READWRITE, &m_VP );
		*( WORD* )( m_Address ) = 0xC069;
		*( DWORD* )( m_Address + 2 ) = Value;
		m_VP = m_VP;
		VirtualProtect( ( void* )( m_Address ), 6, m_VP, &m_VP );
		m_Address += 6;
	};
};

void CAssembly::MovEax( int Var)
{
	if( Var == ESI )
	{
		VirtualProtect( ( void* )( m_Address ), 2, PAGE_EXECUTE_READWRITE, &m_VP );
		*( WORD* )( m_Address ) = 0xC68B;
		m_VP = m_VP;
		VirtualProtect( ( void* )( m_Address ), 2, m_VP, &m_VP );
		m_Address += 2;
	};
};