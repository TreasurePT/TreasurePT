#pragma once

class FileManager
{
public:
	FileManager( );
	FileManager( const char* FileName );
	void SetName( const char* FileName );
	int ReadInt( const char* Section, const char* Key );
	void ReadString( const char* Section, const char* Key, char* Buffer );
	void DeleteThisFile( ) { DeleteFileA( File.FullPath ); };
	bool FileExists()
	void Write( const char* Section, const char* Key, const char* String );
protected:

private:
	struct s_File
	{
		char Name[ 256 ];
		char Directory[ 512 ];
		char FullPath[ 512 + 256 ];
	} File;

};