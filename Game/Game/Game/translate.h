#pragma once
class CTranslate
{
public:
	CTranslate( );
	void Translate( long Address, const char* Text, ... );
	void SetTexts( );
private:
	static long m_Address_Text, m_Spacements;
};

class CSkillTranslate
{
public:
	CSkillTranslate( );
	void Name( const char* Text, ... );
	void Description( const char* Text, ... );
	void SetTexts( );
private:
	static long m_Address_Text, m_Spacements;
};

class CDoubleTextTranslate
{
public:
	CDoubleTextTranslate( );
	void Text1( const char* Text, ... );
	void Text2( const char* Text, ... );
	void SetTexts( );
private:
	static long m_Address_Text, m_Spacements;
};