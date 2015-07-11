#pragma once
class CTranslate
{
public:
	CTranslate( );
	void Translate( int Address, const char* Text, ... );
	void SetTexts( );
private:
	static int m_Address_Text, m_Spacements;
};

class CSkillTranslate
{
public:
	CSkillTranslate( );
	void Name( const char* Text, ... );
	void Description( const char* Text, ... );
	void SetTexts( );
private:
	static int m_Address_Text, m_Spacements;
};