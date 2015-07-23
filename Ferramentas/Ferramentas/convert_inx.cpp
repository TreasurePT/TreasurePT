#include "stdafx.h"
#include "convert_inx.h"

FILE* lpDbg = nullptr;

void ConvertInx::Convert( s_Inx* InxFile )
{
	FILE* lpFile = nullptr;
	fopen_s( &lpFile, InxFile->FullPath, "rb" );
	if( !lpFile )
	{
		fprintf( lpDbg, "ERRO      : %s\n", InxFile->FullPath );
		return;
	};
	fprintf( lpDbg, "Convertido: %s\n", InxFile->FullPath );
	char DataFile[ 95268 ] = { 0 };
	int Bytes = fread_s( &DataFile, 95268, 95268, 1, lpFile );
	char NewData[ 67084 ] = { 0 };
	fclose( lpFile );

	FILE* Backup = nullptr;
	fopen_s( &Backup, Format( "%s_old", InxFile->FullPath ), "wb+" );
	fwrite( DataFile, sizeof( char ), sizeof( DataFile ), Backup );
	fclose( Backup );
	
	DeleteFileA( InxFile->FullPath );
	FILE* NewFile = nullptr;
	fopen_s( &NewFile, InxFile->FullPath, "wb+" );

	int j = 0;
	for( int i = 0; i < 95268; i++ )
	{
		if( j == 0x63C )
		{
			i = 0x844;
		}
		if( j == 0x6A8 )
		{
			i = 0x8E4;
		}
		if( j == 0x720 )
		{
			i = 0x990;
		}
		if( j == 0x798 )
		{
			i = 0xA3C;
		}
		if( j == 0x814 )
		{
			i = 0xAEC;
		}
		if( j == 0x88C )
		{
			i = 0xB98;
		}
		if( j == 0x904 )
		{
			i = 0xC44;
		}
		if( j == 0x97C )
		{
			i = 0xCF0;
		}
		if( j == 0x9F4 )
		{
			i = 0xD9C;
		}
		if( j == 0xA6C )
		{
			i = 0xE48;
		}
		if( j == 0xAE4 )
		{
			i = 0xB18;
		}
		if( j == 0xB5C )
		{
			i = 0xBC4;
		}
		if( j == 0xBD4 )
		{
			i = 0xC70;
		}
		if( j == 0xF18C )
		{
			i = 0x1598C;
		}
		if( j == 0x10068 )
		{
			i = 0x16E80;
		}
		NewData[ j ] = DataFile[ i ];
		j++;
	}

	fwrite( &NewData, sizeof( char ), sizeof( NewData ), NewFile );
	fclose( NewFile );
};

void ConvertInx::ConvertMonster( const char* Directory )
{
	hDirectory = FindFirstFileA( Format( "%s\\char\\monster\\*", Directory ), &DirAttr );
	s_Inx InxFile = { 0 };
	while( true )
	{
		if( hDirectory != INVALID_HANDLE_VALUE )
		{
			if( DirAttr.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY )
				break;

			if( DirAttr.dwFileAttributes == FILE_ATTRIBUTE_HIDDEN )
				break;

			hFile = FindFirstFileA( Format( "%s\\char\\monster\\%s\\*.inx", Directory, DirAttr.cFileName ), &FileAttr );
			while( true )
			{
				if( FileAttr.cFileName[ lstrlenA( FileAttr.cFileName ) - 1 ] == 'x' )
				{
					if( FileAttr.nFileSizeLow == 95268 )
					{
						StringCbCopyA( InxFile.FileName, 256, FileAttr.cFileName );
						StringCbCopyA( InxFile.FullPath, 512, Format( "%s\\char\\monster\\%s\\%s",
							Directory, DirAttr.cFileName, FileAttr.cFileName ) );
						Convert( &InxFile );
					};
				};

				if( FindNextFileA( hFile, &FileAttr ) == FALSE )
					break;
			};

			if( FindNextFileA( hDirectory, &DirAttr ) == FALSE )
				break;
		}
		else
			break;
	};
	hDirectory = NULL;
	hFile = NULL;
	SecureZeroMemory( &DirAttr, sizeof( WIN32_FIND_DATA ) );
	SecureZeroMemory( &FileAttr, sizeof( WIN32_FIND_DATA ) );
};

void ConvertInx::ConvertNpc( const char* Directory )
{
	hDirectory = FindFirstFileA( Format( "%s\\char\\npc\\*", Directory ), &DirAttr );
	s_Inx InxFile = { 0 };
	while( true )
	{
		if( hDirectory != INVALID_HANDLE_VALUE )
		{
			if( DirAttr.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY )
				break;

			if( DirAttr.dwFileAttributes == FILE_ATTRIBUTE_HIDDEN )
				break;

			hFile = FindFirstFileA( Format( "%s\\char\\npc\\%s\\*.inx", Directory, DirAttr.cFileName ), &FileAttr );
			while( true )
			{
				if( FileAttr.cFileName[ lstrlenA( FileAttr.cFileName ) - 1 ] == 'x' )
				{
					if( FileAttr.nFileSizeLow == 95268 )
					{
						StringCbCopyA( InxFile.FileName, 256, FileAttr.cFileName );
						StringCbCopyA( InxFile.FullPath, 512, Format( "%s\\char\\npc\\%s\\%s",
							Directory, DirAttr.cFileName, FileAttr.cFileName ) );
						Convert( &InxFile );
					};
				};

				if( FindNextFileA( hFile, &FileAttr ) == FALSE )
					break;
			};

			if( FindNextFileA( hDirectory, &DirAttr ) == FALSE )
				break;
		}
		else
			break;
	};
	hDirectory = NULL;
	hFile = NULL;
	SecureZeroMemory( &DirAttr, sizeof( WIN32_FIND_DATA ) );
	SecureZeroMemory( &FileAttr, sizeof( WIN32_FIND_DATA ) );
};

ConvertInx::ConvertInx( )
{
	char Directory[ 512 ] = { 0 };
	GetCurrentDirectoryA( 512, Directory );
	DeleteFileA( "Logs.txt" );
	fopen_s( &lpDbg, "Logs.txt", "a" );
	ConvertMonster( Directory );
	ConvertNpc( Directory );
	fclose( lpDbg );
}