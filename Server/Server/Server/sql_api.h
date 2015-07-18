#pragma once
#include <vector>

typedef std::vector<std::vector<std::string>> SQLPTR;

class CSQLApi
{
public:
	bool Select( SQLPTR &Buffer, const char* Query, ... );
	bool Execute( const char* Query, ... );
protected:
	static void* s_Env,* s_Conn;
private:
	char m_Query[ 256 ];
	short m_Column;
	void* m_Statement;
	SQLPTR m_Values;
	std::string m_Buffer;
};