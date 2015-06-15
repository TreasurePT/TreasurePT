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