#pragma once

#define OLD_INX_SIZE 95268
#define NEW_INX_SIZE 67084

class ConvertInx
{
private:
	struct s_Inx
	{
		char FullPath[ 512 ];
		char FileName[ 256 ];
	};
public:
	ConvertInx( );
	void ConvertMonster( const char* Directory );
	void ConvertNpc( const char* Directory );
	void Convert( s_Inx* InxFile );
	const char* GetName( const char* FullPath );
private:
	WIN32_FIND_DATAA DirAttr, FileAttr;
	HANDLE hFile, hDirectory;
};