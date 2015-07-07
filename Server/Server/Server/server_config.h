#pragma once
class CServerConfig
{
public:
	CServerConfig( ) { Loaded = false; };
	void ReadHotuk( );
	void SetHotukValues( );
	static std::shared_ptr<CServerConfig> s_lpSvConfig;
private:
	bool Loaded;
	struct s_Server
	{
		int MaxUsers;
		char InternalProtocol[ 32 ];
		int Version;
		char LogPath[ 256 ];
		int CheckSum;
	} Server;
	struct s_GameServer
	{
		char Name[ 128 ];
		char InternalProtocol[ 32 ];
	} GameServer[ 3 ];
	struct s_Permission
	{
		char ID[ 32 ];
		char Permission[ 16 ];
	} Permission[ 5 ];
	struct s_Clan
	{
		char InternalProtocol[ 32 ];
	} Clan;
	struct s_Sql
	{
		char Instance[ 64 ];
		char User[ 32 ];
		char Password[ 32 ];
	} Sql;
	struct s_Config
	{
		char WelcomeMsg[ 256 ];
		int ExpRate;
		int BattleField;
	} Config;
};