#include "stdafx.h"
#include "sql_api.h"
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>

SQLHANDLE CSQLApi::s_Env = nullptr;
SQLHANDLE CSQLApi::s_Conn = nullptr;

bool CSQLApi::Select( SQLPTR &Buffer, const char* Query, ... )
{
	Clear( m_Query, 256 );
	m_Statement = NULL;
	Buffer.clear( );
	m_Buffer.clear( );
	m_Buffer.resize( 200 );
	m_Column = NULL;

	va_list Args;
	va_start( Args, Query );
	StringCbVPrintfA( m_Query, 256, Query, Args );
	va_end( Args );

	SQLAllocHandle( SQL_HANDLE_STMT, s_Conn, &m_Statement );
	SQLExecDirectA( m_Statement, ( SQLCHAR* )m_Query, SQL_NTS );
	SQLNumResultCols( m_Statement, &m_Column );

	bool HasResult = false;
	int j = 0;

	while( SQLFetch( m_Statement ) == SQL_SUCCESS )
	{
		HasResult = true;
		Buffer.resize( j + 1 );
		for( int i = 1; i <= m_Column; i++ )
		{
			SQLGetData( m_Statement, i, SQL_C_CHAR, ( char* )m_Buffer.c_str( ), 200, NULL );
			Buffer[ j ].resize( i );
			Buffer[ j ][ i - 1 ] = m_Buffer;
		};
		j++;
	}

	SQLFreeHandle( SQL_HANDLE_STMT, m_Statement );
	return HasResult;
};

bool CSQLApi::Execute( const char* Query, ... )
{
	Clear( m_Query, 256 );
	m_Statement = NULL;

	va_list Arguments;
	va_start( Arguments, Query );
	if( StringCbVPrintfA( m_Query, 256, Query, Arguments ) >= 0 )
	{
		va_end( Arguments );

		SQLAllocHandle( SQL_HANDLE_STMT, s_Conn, &m_Statement );
		SQLExecDirectA( m_Statement, ( SQLCHAR* )m_Query, SQL_NTS );
		SQLFreeHandle( SQL_HANDLE_STMT, m_Statement );
		return true;
	}
	else
	{
		va_end( Arguments );
		return false;
	}
};