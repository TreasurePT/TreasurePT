#include "stdafx.h"
#include "file_manager.h"


CFileManager::CFileManager( const char* FileName )
{
	StringCbCopyA( File.Name, 256, FileName );
	GetCurrentDirectoryA( 512, File.Directory );
	StringCbPrintfA( File.FullPath, 512 + 256, "%s\\%s", File.Directory, File.Name );
};

void CFileManager::SetFileName( const char* FileName )
{
	StringCbCopyA( File.Name, 256, FileName );
	GetCurrentDirectoryA( 512, File.Directory );
	StringCbPrintfA( File.FullPath, 512 + 256, "%s\\%s", File.Directory, File.Name );
};

void CFileManager::GetString( const char* Section, const char* Key, char* Buffer )
{
	GetPrivateProfileStringA( Section, Key, 0, Buffer, 256, File.FullPath );
};

void CFileManager::SetString( const char* Section, const char* Key, const char* String )
{
	WritePrivateProfileStringA( Section, Key, String, File.FullPath );
};

void CFileManager::Log( const char* Format, ... )
{
	SecureZeroMemory( m_Buffer, 256 );
	va_list Args;
	va_start( Args, Format );
	StringCbVPrintfA( m_Buffer, 256, Format, Args );

	fopen_s( &m_File, File.Name, "a" );
	SYSTEMTIME Date = { 0 };
	GetLocalTime( &Date );
	fprintf_s( m_File, "[%02d-%02d-%04d]{%02d-%02d-%02d} - %s\n",
			   Date.wDay, Date.wMonth, Date.wYear,
			   Date.wHour, Date.wMinute, Date.wSecond,
			   m_Buffer );
	fclose( m_File );
	va_end( Args );
};


const char* CFileManager::Format( const char* String, ... )
{
	SecureZeroMemory( m_Buffer, 256 );
	va_list Args;
	va_start( Args, String );
	StringCbVPrintfA( m_Buffer, 256, String, Args );
	va_end( Args );
	return m_Buffer;
};