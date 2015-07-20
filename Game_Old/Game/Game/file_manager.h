#pragma once
class CFileManager
{
public:
	CFileManager( ) { };
	CFileManager( const char* FileName );

	void GetString( const char* Section, const char* Key, char* Buffer );
	void SetString( const char* Section, const char* Key, const char* String );
private:
	struct s_File
	{
		char Name[ 256 ];
		char Directory[ 512 ];
		char FullPath[ 512 + 256 ];
	} File;
};