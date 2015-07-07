#include "stdafx.h"
#include "server_config.h"
#include "file_manager.h"

std::shared_ptr<CServerConfig> CServerConfig::s_lpSvConfig = nullptr;

void CServerConfig::ReadHotuk( )
{
	if( !Loaded )
	{
		std::shared_ptr<CFileManager> lpFile = std::make_shared<CFileManager>( "hotuk.ini" );
		Loaded = true;
		lpFile->GetInt( "Servidor", "Maximo de Usuarios", Server.MaxUsers );
		lpFile->GetString( "Servidor", "Protocolo Interno", Server.InternalProtocol );
		lpFile->GetInt( "Servidor", "Versao", Server.Version );
		lpFile->GetString( "Servidor", "Pasta de Logs", Server.LogPath );
		lpFile->GetInt( "Servidor", "CheckSum", Server.CheckSum );

		for( int i = 0; i < 3; i++ )
		{
			lpFile->GetString( "Servidores de Jogo",
							   lpFile->Format( "%d- Nome do Servidor", ( i + 1 ) ),
							   GameServer[ i ].Name );
			lpFile->GetString( "Servidores de Jogo",
							   lpFile->Format( "%d- Protocolo Interno", ( i + 1 ) ),
							   GameServer[ i ].InternalProtocol );
		};

		for( int i = 0; i < 5; i++ )
		{
			lpFile->GetString( "Permissoes",
							   lpFile->Format( "%d- ID", ( i + 1 ) ),
							   Permission[ i ].ID );
			lpFile->GetString( "Permissoes",
							   lpFile->Format( "%d- Permissao", ( i + 1 ) ),
							   Permission[ i ].Permission );
		};

		lpFile->GetString( "Clan", "Protocolo Interno", Clan.InternalProtocol );

		lpFile->GetString( "Sql", "Instancia", Sql.Instance );
		lpFile->GetString( "Sql", "Usuario", Sql.User );
		lpFile->GetString( "Sql", "Senha", Sql.Password );

		lpFile->GetString( "Configuracoes", "Mensagem de Boas Vindas", Config.WelcomeMsg );
		lpFile->GetInt( "Configuracoes", "Taxa de Experiencia", Config.ExpRate );
		lpFile->GetInt( "Configuracoes", "Mapa de Batalha", Config.BattleField );
	};
};

void CServerConfig::SetHotukValues( )
{
	if( Loaded )
	{
		// *MODE SERVER
		*( int* )( 0x008487B8 ) = -1;
		// *SERVER_CODE 0 && *SERVER_AUTOPLAY
		*( int* )( 0x008487BC ) = 0;
		*( int* )( 0x008487C0 ) = 0;

	};
};