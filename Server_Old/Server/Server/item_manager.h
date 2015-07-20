#pragma once
class CItemManager
{
public:
	void BuildItems( );
	void ReferenceItems( );
	void CreateItem( int ID, const char* Code1, const char* Code2, int Width,
					 int Height, const char* Folder, int Hand, int City,
					 int Sound, int Range, int Unknown );
private:
	int m_Item_Address, m_Number_of_Items;
};

