#pragma once
class CItemManager
{
public:
	void BuildItems( );
	void ReferenceItems( );
	void CreateItem( long ID, const char* Code1, const char* Code2, long Width,
					 long Height, const char* Folder, long Hand, long City,
					 long Sound, long Range, long Unknown );
private:
	long m_Item_Address, m_Number_of_Items;
};

