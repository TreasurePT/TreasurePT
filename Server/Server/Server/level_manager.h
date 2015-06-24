#pragma once
class CLevelManager
{
public:
	long CheckExpGained( long Exp, long Player );
private:
	long m_Player_GmLevel, m_Player_Level;
};