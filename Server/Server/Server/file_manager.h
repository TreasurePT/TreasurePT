#pragma once

class CFileManager
{
public:
	CFileManager( const char* FileName );

	void SetFileName( const char* FileName );
	void GetString( const char* Section, const char* Key, char* Buffer );
	void GetInt( const char* Section, const char* Key, int &Buffer );
	void SetString( const char* Section, const char* Key, const char* String );
	void Log( const char* Format, ... );

	const char* Format( const char* String, ... );

private:
	struct s_File
	{
		char Name[ 256 ];
		char Directory[ 512 ];
		char FullPath[ 512 + 256 ];
	} File;

	char m_Buffer[ 256 ];
	FILE* m_File;
};

