#include "stdafx.h"
#include "settings.h"
#include "file_manager.h"

Settings::Settings( )
{
	SecureZeroMemory( &Setting, sizeof( s_Settings ) );
	Read( );
	Write( );
}

void Settings::Read( )
{
	std::shared_ptr<FileManager> File = std::make_shared<FileManager>( "game\\game.ini" );
	bool Error = false;

	char Buffer[ 256 ] = { 0 };

	File->ReadString( "Vídeo", "Janela", Buffer );

	if( Buffer[ 0 ] == 0 )
		Error = true;

	if( lstrcmpiA( Buffer, "Desativado" ) == 0 )
	{
		Setting.WindowMode = false;
	}
	else
	{
		Setting.WindowMode = true;
	};

	struct s_Resolutions
	{
		int Width;
		int Height;
		bool isWide;
	};

	s_Resolutions Resolutions[ ] =
	{
		{ 800, 600, false },
		{ 1024, 768, false },
		{ 1280, 1024, false }
	};

	Setting.Width = File->ReadInt( "Vídeo", "Largura" );
	Setting.Height = File->ReadInt( "Vídeo", "Altura" );

	if( Setting.Width == 0 || Setting.Height == 0 )
		Error = true;

	bool ValidResolution = false;
	for( int i = 0; i < 3; i++ )
	{
		if( Setting.Width == Resolutions[ i ].Width &&
			Setting.Height == Resolutions[ i ].Height )
		{
			ValidResolution = true;
			Setting.isWide = Resolutions[ i ].isWide;
		};
	};

	if( !ValidResolution )
	{
		Setting.Width = 800;
		Setting.Height = 600;
	};

	Setting.Bpp = File->ReadInt( "Gráficos", "Cores" );

	if( Setting.Bpp == 0 )
		Error = true;

	if( Setting.Bpp != 16 && Setting.Bpp != 32 )
		Setting.Bpp = 32;

	File->ReadString( "Gráficos", "Qualidade", Buffer );

	if( Buffer[ 0 ] == 0 )
		Error = true;

	if( lstrcmpiA( Buffer, "Mínima" ) == 0 )
	{
		Setting.Quality = 3;
	}
	else if( lstrcmpiA( Buffer, "Baixa" ) == 0 )
	{
		Setting.Quality = 2;
	}
	else if( lstrcmpiA( Buffer, "Média" ) == 0 )
	{
		Setting.Quality = 1;
	}
	else
	{
		Setting.Quality = 0;
	};

	File->ReadString( "Gráficos", "Blur", Buffer );

	if( Buffer[ 0 ] == 0 )
		Error = true;

	if( lstrcmpiA( Buffer, "Desativado" ) == 0 )
	{
		Setting.Blur = false;
	}
	else
	{
		Setting.Blur = true;
	};

	File->ReadString( "Câmera", "Distância", Buffer );

	if( Buffer[ 0 ] == 0 )
		Error = true;

	if( lstrcmpiA( Buffer, "Perto" ) == 0 )
	{
		Setting.Distance = false;
	}
	else
	{
		Setting.Distance = true;
	};

	File->ReadString( "Câmera", "Inverter", Buffer );

	if( Buffer[ 0 ] == 0 )
		Error = true;

	if( lstrcmpiA( Buffer, "Desativado" ) == 0 )
	{
		Setting.Inverted = false;
	}
	else
	{
		Setting.Inverted = true;
	};

	File->ReadString( "Som", "Som", Buffer );

	if( Buffer[ 0 ] == 0 )
		Error = true;

	if( lstrcmpiA( Buffer, "Desativado" ) == 0 )
	{
		Setting.Sound = false;
	}
	else
	{
		Setting.Sound = true;
	};

	for( int i = 0; i < 10; i++ )
	{
		File->ReadString( "Atalhos", Format( "Atalho%d", i + 1 ), Buffer );
		StringCbCopyA( Setting.Macro[ i ], 256, Buffer );
	};

	File->ReadString( "Game Master", "Adm", Buffer );
	if( Buffer[ 0 ] != 0 )
	{
		if( lstrcmpA( Buffer, "Ativado" ) == 0 )
		{
			Setting.isGm = true;
		};
	};

	if( Error )
		CreateIni( );
};

void Settings::Write( )
{
	*( int* )( 0x00D0A540 ) = Setting.WindowMode;
	*( int* )( 0x00D0A544 ) = Setting.Width;
	*( int* )( 0x00D0A548 ) = Setting.Height;
	if( Setting.Bpp == 16 )
		*( int* )( 0x00D0A54C ) = Setting.Bpp;
	else
		*( int* )( 0x00D0A54C ) = 0;
	*( int* )( 0x00D0A550 ) = Setting.Quality;
	*( int* )( 0x024785F8 ) = Setting.Blur;
	*( int* )( 0x00A45594 ) = Setting.Distance;
	*( int* )( 0x00A45590 ) = Setting.Inverted;
	*( int* )( 0x00D0A554 ) = Setting.Sound;

	StringCbCopyA( ( char* )( 0x00D0C1D8 ), 16, IP );
	StringCbCopyA( ( char* )( 0x00D0C1B4 ), 16, IP );
	StringCbCopyA( ( char* )( 0x00D0C220 ), 16, IP );
	StringCbCopyA( ( char* )( 0x00D0C1FC ), 16, IP );

	for( int i = 0; i < 10; i++ )
	{
		for( int c = 0; c < 100; c++ )
		{
			if( Setting.Macro[ i ][ c ] == '\\' &&
				( Setting.Macro[ i ][ c + 1 ] == 'r' ||
				Setting.Macro[ i ][ c + 1 ] == 'R' ) )
			{
				Setting.Macro[ i ][ c ] = 0x0D;
				Setting.Macro[ i ][ c + 1 ] = 0;
				break;
			};
			if( Setting.Macro[ i ][ c ] == 0x0A ||
				Setting.Macro[ i ][ c ] == 0x0D )
			{
				Setting.Macro[ i ][ c + 1 ] = 0;
				break;
			};
		};
		StringCbCopyA( ( char* )( 0x00D0A158 + i * 100 ), 100, Setting.Macro[ i ] );
	};

	*( int* )( 0x00D0C244 ) = ( int )( Setting.isGm * 0x100 );
};

void Settings::CreateIni( )
{
	std::shared_ptr<FileManager> File = std::make_shared<FileManager>( "game\\game.ini" );
	File->DeleteThisFile( );
	File->Write( "Vídeo", "Janela", "Ativado" );
	File->Write( "Vídeo", "Largura", "800" );
	File->Write( "Vídeo", "Altura", "600" );
	File->Write( "Gráficos", "Cores", "32" );
	File->Write( "Gráficos", "Qualidade", "Alta" );
	File->Write( "Gráficos", "Blur", "Desativado" );
	File->Write( "Câmera", "Distância", "Longe" );
	File->Write( "Câmera", "Inverter", "Desativado" );
	File->Write( "Som", "Som", "Ativado" );

	for( int i = 0; i < 10; i++ )
	{
		File->Write( "Atalhos", Format( "Atalho%d", i + 1 ), "" );
	};

	MessageBoxA( NULL,
				 "Foi encontrado um erro no arquivo de Configurações.O arquivo foi restaurado com as configurações padrões."
				 "TreasurePT", MB_OK | MB_ICONEXCLAMATION );
};

void __cdecl Game_Settings( )
{
	std::shared_ptr<Settings> Setting = std::make_shared<Settings>( );
};